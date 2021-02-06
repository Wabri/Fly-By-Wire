#include "wes.h"
#include "config.h"
#include "string.h"
#include "transducer.h"
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>

void wes(int *pidPFCs)
{

    char *logPathName = malloc(1 + strlen(WES_LOGS_PATH) + strlen(WES_LOGS));
    strcpy(logPathName, WES_LOGS_PATH);
    strcat(logPathName, WES_LOGS);
    FILE *logFile = fopen(logPathName, "w+");
    free(logPathName);

    SpeedWesPFC *swpfc = malloc(sizeof(SpeedWesPFC[3]));
    for (int i = 0; i < 3; i++)
    {
        swpfc[i].speedLogPath = extractTransSpeedLogName(TRANS_SPFCS_LOGS);
    }
    for (int index = 0; index < 3; index++)
    {
        do
        {
            swpfc[index].logFile = fopen(swpfc[index].speedLogPath, "r");
        } while (swpfc[index].logFile == NULL);

        fprintf(logFile, "speedPFC%d open correctly\n", index);
        swpfc[index].counter = -1;
        swpfc[index].speed = -1;
        swpfc[index].filePosition = 0;
    }

    conMeta *pCM = malloc(sizeof(conMeta));

    createPipeServer(pCM, PIPE_PFCDS_WES);

    while (1) ////case
    {
        // sock
        int result1 = extractSpeedInfos(&swpfc[0]);
        // pipe
        int result2 = extractSpeedInfos(&swpfc[1]);
        // file
        int result3 = extractSpeedInfos(&swpfc[2]);
        // processing
        char *data;
        if ((result1 == result2) && (result1 == result3) && (result1 == -1))
        {
            data = malloc(1 + strlen(PFCDS_EXIT_SIGNAL));
            sprintf(data, "%s", PFCDS_EXIT_SIGNAL);
            sendDataToPFCDS(pCM, data);
            fprintf(logFile, "%s\n", data);
            break;
        }
        int pidLength;
        if ((swpfc[0].counter == swpfc[1].counter) && (swpfc[0].speed == swpfc[1].speed))
        {
            if ((swpfc[0].counter == swpfc[2].counter) && (swpfc[0].speed == swpfc[2].speed))
            {
                fprintf(logFile, "%s\n", PFCDS_OK_SIGNAL);
            }
            else
            {
                pidLength = (int)((ceil(log10(pidPFCs[2])) + 1) * sizeof(char));
                data = malloc(1 + strlen(PFCDS_ERROR_SIGNAL) + 1 + pidLength);
                sprintf(data, "%s %d", PFCDS_ERROR_SIGNAL, pidPFCs[2]);
                sendDataToPFCDS(pCM, data);
                fprintf(logFile, "%s\n", data);
            }
        }
        else if (swpfc[0].counter == swpfc[2].counter)
        {
            pidLength = (int)((ceil(log10(pidPFCs[1])) + 1) * sizeof(char));
            data = malloc(1 + strlen(PFCDS_ERROR_SIGNAL) + 1 + pidLength);
            sprintf(data, "%s %d", PFCDS_ERROR_SIGNAL, pidPFCs[1]);
            sendDataToPFCDS(pCM, data);
            fprintf(logFile, "%s\n", data);
        }
        else if (swpfc[1].counter == swpfc[2].counter)
        {
            pidLength = (int)((ceil(log10(pidPFCs[0])) + 1) * sizeof(char));
            data = malloc(1 + strlen(PFCDS_ERROR_SIGNAL) + 1 + pidLength);
            sprintf(data, "%s %d", PFCDS_ERROR_SIGNAL, pidPFCs[0]);
            sendDataToPFCDS(pCM, data);
            fprintf(logFile, "%s\n", data);
        }
        else
        {
            data = malloc(1 + strlen(PFCDS_EMERGENCY_SIGNAL));
            sprintf(data, "%s", PFCDS_EMERGENCY_SIGNAL);
            sendDataToPFCDS(pCM, data);
            fprintf(logFile, "%s\n", data);
        }
        fprintf(logFile, " %d:%f %d:%f %d:%f\n", swpfc[0].counter,
                swpfc[0].speed, swpfc[1].counter, swpfc[1].speed,
                swpfc[2].counter, swpfc[2].speed);
        fflush(logFile);
        sleep(CLOCK);
    }
    fclose(logFile);
}

int extractSpeedInfos(SpeedWesPFC *wes)
{
    char *data = malloc(sizeof(char[64]));
    char *temp = malloc(sizeof(char[64]));
    int tempCounter;
    int cycleDone = 0;
    while (1)
    {
        if (cycleDone > 2)
            return 0;
        else
            cycleDone += 1;
        fseek(wes->logFile, wes->filePosition, SEEK_SET);
        fgets(data, 64, wes->logFile);
        if (!strcmp(data, STOP_SIGNAL))
            return -1;
        if (strlen(data) < 4)
            continue;
        strExtrSeparator(temp, data, " ");
        tempCounter = atoi(temp);
        if (tempCounter == wes->counter)
        {
            cycleDone = 0;
            continue;
        }
        break;
    }
    wes->counter = tempCounter;
    strExtrInterval(
        temp,
        data,
        strSeparatorIndex(data, ' ') + 1,
        strSeparatorIndex(data, '\0'));
    wes->speed = atof(temp);
    if (strlen(data) > 1)
        wes->filePosition += strlen(data);
    else
        wes->filePosition += 11;
    rewind(wes->logFile);
    return 0;
}

void sendDataToPFCDS(conMeta *pCM, char *data)
{
    write(pCM->fdServer, data, strlen(data) + 1);
    wait(NULL); //log?
}
