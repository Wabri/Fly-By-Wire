#include "pfc.h"
#include "../utility/string.h"
#include "../utility/connection.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void pfc(char *name, char *filePath, char *logPath, char *sentence) {
    // printf("pfc: %d\n", getpid());
    PFC pfc, *ppfc = &pfc;
    PTP ptp, *pptp = &ptp;
    ppfc->name = name;
    ppfc->filePath = filePath;

    char *logPathName = malloc(1 + strlen(logPath) + strlen("log_") +
            strlen(ppfc->name) + strlen(".txt"));
    logPathName[0] = '\0';

    strcat(logPathName, logPath);
    strcat(logPathName, "log_");
    strcat(logPathName, ppfc->name);
    strcat(logPathName, ".txt");

    ppfc->fileLog = logPathName;

    importNMEA(ppfc, pptp, sentence);
}

void importNMEA(PFC *pPFC, PTP *pPointToPoint, char *sElement) {
    char sLine[255];
    char sRecordHead[255];
    FILE *pFile, *pLog;
    PTP *pPTP = pPointToPoint;
    sockMeta sM, *pSM = &sM;
    pFile = fopen(pPFC->filePath, "r");
    pLog = fopen(pPFC->fileLog, "w+");

    if (pFile == NULL) {
        exit(EXIT_FAILURE);
    }

    // TODO: is it worth open connection here?
    createSocketServer(pSM);

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
            // TODO: verify sprintf
            //sprintf(sInstantSpeed, "%f" , pPTP->istantSpeed);
            //while (1) {
            //    pSM->fdClient = accept(pSM->fdServer, (struct sockaddr *) pSM->pSerAdd, &(pSM->iLength));
            //    if (fork() == 0) {
            //        write(pSM->fdClient,sInstantSpeed, strlen(sInstantSpeed) + 1);
            //        close(pSM->fdClient);
            //        exit(EXIT_SUCCESS);
            //    } else {
            //        close(pSM->fdClient);
            //    }
            //}

            if (NULL != pPTP->next) {
                pPTP = pPTP->next;
            }
            fprintf(pLog, "%d catch: %s", getpid(), sLine);
        }
        // sleep(1);
    };

    fclose(pFile);
    fclose(pLog);
}

