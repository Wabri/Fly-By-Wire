#include "pfc.h"
#include "../utility/string.h"
#include "../constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

void pfc(char *name, char *filePath, char *logPath, char *sentence, unsigned int connectionType) {
    PFC pfc, *ppfc = &pfc;
    PTP ptp, *pptp = &ptp;
    ppfc->name = name;
    ppfc->filePath = filePath;

    char *logPathName = malloc(1 + strlen(logPath) +
            strlen(ppfc->name) + strlen(".txt"));
    
    strcpy(logPathName, logPath);
    strcat(logPathName, "raw");
    strcat(logPathName, ppfc->name);
    strcat(logPathName, ".log");

    ppfc->fileLog = logPathName;

    parseNMEA(ppfc, pptp, sentence, connectionType);
}

void parseNMEA(PFC *pPFC, PTP *pPointToPoint, char *sElement, unsigned int connectionType) {
    char sLine[255];
    char sRecordHead[255];
    FILE *pFile, *pLog;
    PTP *pPTP = pPointToPoint;
    pFile = fopen(pPFC->filePath, "r");
    pLog = fopen(pPFC->fileLog, "w+");

    if (pFile == NULL) {
        exit(EXIT_FAILURE);
    }

    conMeta *pCM = malloc(sizeof(conMeta));
    pCM->connectionType = connectionType;
    fprintf(pLog, "Open server connection\n");
    generateConnectionWithTrans(pCM);

    while (fgets(sLine, sizeof(sLine), pFile) != NULL) {
        strExtrSeparator(sRecordHead, sLine, ",");
        fprintf(pLog, "Compare %s with  %s\n", sElement, sRecordHead);
        if (strcmp(sRecordHead, sElement) == 0) {
            fprintf(pLog, "\tCatch: %s\n", sLine);
            RawElement *pRawElement = (RawElement *)malloc(sizeof(RawElement));
            extractRawElements(pRawElement, sLine);
            GLL *pGLL = (GLL *)malloc(sizeof(GLL));
            extractGLL(pGLL, pRawElement);
            addPoint(pPTP, pGLL);

            char *sInstantSpeed = malloc(sizeof(char[255]));
            sprintf(sInstantSpeed, "%f" , pPTP->istantSpeed);
            fprintf(pLog, "\tSend to Transducer %s\n", sLine);
            sendDataToTrans(pCM, sInstantSpeed);

            if (NULL != pPTP->next) {
                pPTP = pPTP->next;
            }

        }
    };

    fprintf(pLog, "No more data on file\n");
    fprintf(pLog, "\tStop connection with Transducer\n");
    stopConnection(pCM);

    fclose(pFile);
    fclose(pLog);
}

void generateConnectionWithTrans(conMeta *pCM) {
    switch (pCM->connectionType) {
        case PFC_TRANS_SOCKET:
            createSocketServer(pCM, SOCK_TRANS_NAME);
            pCM->fdClient = accept(pCM->fdServer, pCM->pCliAdd, &(pCM->cliLen));
            break;
        case PFC_TRANS_PIPE:
            createPipeServer(pCM, PIPE_TRANS_NAME);
            break;
        case PFC_TRANS_FILE:
            break;
    }
}

void sendDataToTrans(conMeta *pCM, char *data) {
    switch (pCM->connectionType) {
        case PFC_TRANS_SOCKET:
            write(pCM->fdClient, data, strlen(data) + 1);
            wait(NULL);
            sleep(CLOCK);
            break;
        case PFC_TRANS_PIPE:
            write(pCM->fdServer, data, strlen(data) + 1);
            wait(NULL);
            sleep(CLOCK);
            break;
        case PFC_TRANS_FILE:
            do {
                pCM->pFile = fopen(FILE_TRANS_NAME, "w+");
                if (pCM->pFile != NULL) {
                    break;
                }
                sleep(CLOCK);
            } while (1);
            fputs(data, pCM->pFile);
            fclose(pCM->pFile);
            sleep(CLOCK);
            break;
    }
}

void stopConnection(conMeta *pCM) {
    sendDataToTrans(pCM, STOP_SIGNAL);
    switch (pCM->connectionType) {
        case PFC_TRANS_SOCKET:
            break;
        case PFC_TRANS_PIPE:
            close(pCM->fdServer);
            break;
        case PFC_TRANS_FILE:
            break;
    }
}
