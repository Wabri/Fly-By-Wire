#include "transducer.h"
#include "../constants.h"
#include "../utility/connection.h"
#include "../utility/string.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

void transducer() {

    // PFC1 Socket
    if (fork() == 0) {
        char *logPath = extractTransLogName(TRANS_SOCK_LOGS);
        FILE *pLog = fopen(logPath, "w+");

        char *speedLogPath = extractTransSpeedLogName(TRANS_SPFCS_LOGS);
        FILE *pSpeedLog = fopen(speedLogPath, "w+");

        conMeta *pCM1 = malloc(sizeof(conMeta));
        fprintf(pLog, "Open socket client connection with PFC1\n");
        createSocketClient(pCM1, SOCK_TRANS_NAME);

        int result = -1;

        do {
            result = connect(pCM1->fdClient, pCM1->pSerAdd, pCM1->serLen);
            if (result == -1) {
                sleep(CLOCK);
            }
        } while (result == -1);

        while (1) {
            char *str = readInstantSpeed(pCM1->fdClient);
            fprintf(pLog, "Received %s from PFC\n", str);
            if (!strcmp(str, STOP_SIGNAL)) {
                fprintf(pLog, "\tStop signal detected on socket\n");
                break;
            }
            fprintf(pSpeedLog, "%s\n", str);
            fflush(pLog);
            fflush(pSpeedLog);
            sleep(CLOCK);
        }

        fprintf(pLog, "Close socket client connection with PFC\n");
        fclose(pLog);
        close(pCM1->fdClient);
        exit(EXIT_SUCCESS);
    }

    // PFC2 Pipe
    if (fork() == 0) {
        char *logPath = extractTransLogName(TRANS_PIPE_LOGS);
        FILE *pLog = fopen(logPath, "w+");

        char *speedLogPath = extractTransSpeedLogName(TRANS_SPFCP_LOGS);
        FILE *pSpeedLog = fopen(speedLogPath, "w+");

        conMeta *pCM2 = malloc(sizeof(conMeta));
        fprintf(pLog, "Open pipe client connection with PFC2\n");
        createPipeClient(pCM2, PIPE_TRANS_NAME);

        while (1) {
            char *str = readInstantSpeed(pCM2->fdClient);
            fprintf(pLog, "Received %s from PFC\n", str);
            if (!strcmp(str, STOP_SIGNAL)) {
                fprintf(pLog, "\tStop signal detected on pipe\n");
                break;
            }
            fprintf(pSpeedLog, "%s\n", str);
            fflush(pSpeedLog);
            sleep(CLOCK);
        }

        fprintf(pLog, "Close socket client connection with PFC\n");
        fclose(pLog);
        close(pCM2->fdClient);
        unlink(PIPE_TRANS_NAME);
        exit(EXIT_SUCCESS);
    }

    // PFC3 FILE
    if (fork() == 0) {
        char *logPath = extractTransLogName(TRANS_FILE_LOGS);
        FILE *pLog = fopen(logPath, "w+");

        char *speedLogPath = extractTransSpeedLogName(TRANS_SPFCF_LOGS);
        FILE *pSpeedLog = fopen(speedLogPath, "w+");

        conMeta *pCM3 = malloc(sizeof(conMeta));
        do{
            pCM3->pFile = fopen(FILE_TRANS_NAME, "r");
            if (pCM3->pFile != NULL) {
                break;
            }
            sleep(CLOCK);
        } while (1);

        int counter = -1;

        while (1) {
            rewind(pCM3->pFile);
            char data[64];
            fgets(data, 64, pCM3->pFile);
            if (!strcmp(data, STOP_SIGNAL)) {
                fprintf(pLog, "\tStop signal detected on file\n");
                break;
            }
            char temp[64];
            strExtrSeparator(temp, data, " ");
            int tempCounter = atoi(temp); 
            if (tempCounter == counter) {
                continue;
                sleep(CLOCK);
            }
            counter = tempCounter;
            fprintf(pLog, "Received %s from PFC\n", data);
            fprintf(pSpeedLog, "%s\n", data);
            fflush(pSpeedLog);
            sleep(CLOCK);
        }
        fprintf(pLog, "Close file client connection with PFC\n");
        fclose(pLog);
        fclose(pCM3->pFile);
        exit(EXIT_SUCCESS);
    }

    wait(NULL);
    wait(NULL);
    wait(NULL);
}

char *readInstantSpeed(int fd) {
    char *str = malloc(16);
    int n = read(fd, str, 16);
    return str;
}

char *extractTransLogName(char *logName) {
    char *temp = malloc(1 + strlen(TRANS_LOGS_PATH) + strlen(logName));
    strcpy(temp, TRANS_LOGS_PATH);
    strcat(temp, logName);
    return temp;
}

char *extractTransSpeedLogName(char *logName) {
    char *temp = malloc(1 + strlen(TRANS_LOGS_PATH) + strlen(logName));
    strcpy(temp, TRANS_LOGS_PATH);
    strcat(temp, logName);
    return temp;
}
