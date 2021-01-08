#include "wes.h"
#include "../constants.h"
#include "../utility/string.h"
#include "../transducer/transducer.h"
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

void wes(int *pidPFCs) {

    char *logPathName = malloc(1 + strlen(WES_LOGS_PATH) + strlen(WES_LOGS));
    strcpy(logPathName, WES_LOGS_PATH);
    strcat(logPathName, WES_LOGS);
    FILE *logFile = fopen(logPathName, "w+");
    free(logPathName);

    SpeedWesPFC *swpfc = malloc(sizeof(SpeedWesPFC[3]));

    swpfc[0].speedLogPath = extractTransSpeedLogName(TRANS_SPFCS_LOGS);
    swpfc[1].speedLogPath = extractTransSpeedLogName(TRANS_SPFCP_LOGS);
    swpfc[2].speedLogPath = extractTransSpeedLogName(TRANS_SPFCF_LOGS);
    for (int index = 0; index < 3; index++) {
        do{
            swpfc[index].logFile = fopen(swpfc[index].speedLogPath, "r");
            if (swpfc[index].logFile != NULL) {
                break;
            }
        } while (1);

        fprintf(logFile, "speedPFC%d open correctly\n", index);
        swpfc[index].counter = -1;
        swpfc[index].speed = -1;
        swpfc[index].filePosition = 0;
    }

    while (1) {
        // sock
        extractSpeedInfos(pidPFCs, &swpfc[0]);
        // pipe
        extractSpeedInfos(pidPFCs, &swpfc[1]);
        // file
        extractSpeedInfos(pidPFCs, &swpfc[2]);
        // processing
        if (swpfc[0].counter == swpfc[1].counter) {
            if (swpfc[0].counter == swpfc[2].counter) {
                fprintf(logFile, "OK %d %d %d\n", swpfc[0].counter, swpfc[1].counter, swpfc[2].counter);
            } else {
                // TODO: send pfcds PFC3 discord 
                fprintf(logFile, "Error %d %d %d\n", swpfc[0].counter, swpfc[1].counter, swpfc[2].counter);
            }
        } else if (swpfc[0].counter == swpfc[2].counter) {
                // TODO: send pfcds PFC2 discord 
                fprintf(logFile, "Error %d %d %d\n", swpfc[0].counter, swpfc[1].counter, swpfc[2].counter);
        } else if (swpfc[1].counter == swpfc[2].counter) {
                // TODO: send pfcds PFC1 discord 
                fprintf(logFile, "Error %d %d %d\n", swpfc[0].counter, swpfc[1].counter, swpfc[2].counter);
        } else {
                // TODO: send pfcds Emergenza
                fprintf(logFile, "EMERGENCY %d %d %d\n", swpfc[0].counter, swpfc[1].counter, swpfc[2].counter);
        }
        fflush(logFile);
        sleep(CLOCK);
    }
    fclose(logFile);
}


void extractSpeedInfos(int *pids, SpeedWesPFC *wes) {
        char *data = malloc(sizeof(char[64]));
        char *temp = malloc(sizeof(char[64]));
        int tempCounter;
        int cycleDone = 0;
        while (1) {
            if (cycleDone > 2) {
                return;
            } else {
                cycleDone += 1;
            }
            fseek(wes->logFile, wes->filePosition, SEEK_SET);
            fgets(data, 64, wes->logFile);
            if (strlen(data) < 4) {
                continue;
            }
            strExtrSeparator(temp, data, " ");
            tempCounter = atoi(temp); 
            if (tempCounter == wes->counter) {
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
        if (strlen(data) > 1) {
            wes->filePosition += strlen(data); 
        } else {
            wes->filePosition += 11;
        }
        rewind(wes->logFile);
}

