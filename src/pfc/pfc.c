#include "pfc.h"
#include "../utility/string.h"
#include "../constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void pfc(char *name, char *filePath, char *logPath, char *sentence, unsigned int connectionType) {
    PFC pfc, *ppfc = &pfc;
    PTP ptp, *pptp = &ptp;
    ppfc->name = name;
    ppfc->filePath = filePath;

    char *logPathName = malloc(1 + strlen(logPath) + strlen("log_") +
            strlen(ppfc->name) + strlen(".txt"));
    logPathName[0] = '\0';

    // TODO: move logs on transducer 
    strcat(logPathName, logPath);
    strcat(logPathName, "log_");
    strcat(logPathName, ppfc->name);
    strcat(logPathName, ".txt");

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

    sockMeta *pSM;
    if (connectionType == PFC_TRANS_SOCKET) {
        startConnectSock(pSM);
    }

    while (fgets(sLine, sizeof(sLine), pFile) != NULL) {
        strExtrSeparator(sRecordHead, sLine, ",");
        fprintf(pLog, "%d compare %s with  %s\n", getpid(), sElement, 
                sRecordHead);
        if (strcmp(sRecordHead, sElement) == 0) {
            RawElement *pRawElement = (RawElement *)malloc(sizeof(RawElement));
            extractRawElements(pRawElement, sLine);
            GLL *pGLL = (GLL *)malloc(sizeof(GLL));
            extractGLL(pGLL, pRawElement);
            addPoint(pPTP, pGLL);

            char *sInstantSpeed = malloc(sizeof(char[255]));
            sprintf(sInstantSpeed, "%f" , pPTP->istantSpeed);
            // TODO: extract send element to transducer
            // TODO: rimane in attesa di un transducer
            if (connectionType == PFC_TRANS_SOCKET) {
                sendTransSock(pSM, sInstantSpeed);
            }

            if (NULL != pPTP->next) {
                pPTP = pPTP->next;
            }
            fprintf(pLog, "%d catch: %s", getpid(), sLine);
        }
    };

    if (connectionType == PFC_TRANS_SOCKET) {
        stopConnectSock(pSM);
    }

    fclose(pFile);
    fclose(pLog);
}

void startConnectSock(sockMeta *pSM) {
    pSM = malloc(sizeof(sockMeta));
    createSocketServer(pSM, SOCK_TRANS_NAME);
}

void stopConnectSock(sockMeta *pSM) {
    pSM->fdClient = accept(pSM->fdServer, pSM->pCliAdd, &(pSM->cliLen));
    if (fork() == 0) {
        char *stop = "stop";
        write(pSM->fdClient, stop, strlen(stop) + 1);
    }                 
    close(pSM->fdClient);
    free(pSM);
}

void sendTransSock(sockMeta *pSM, char *message) {
    pSM->fdClient = accept(pSM->fdServer, pSM->pCliAdd, &(pSM->cliLen));
    if (fork() == 0) {
        write(pSM->fdClient, message, strlen(message) + 1);
    }                 
    close(pSM->fdClient);
}
