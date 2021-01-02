#include "transducer.h"
#include "../constants.h"
#include "../utility/connection.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

void transducer(char *logPath) {


    // PFC1 Socket
    if (fork() == 0) {
        char *logPathName = malloc(1 + strlen(logPath) +
                strlen("speedPFC1.log"));
        strcpy(logPathName, logPath);
        strcat(logPathName, "speedPFC1.log");
        FILE *pLog = fopen(logPathName, "w+");

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
            sleep(CLOCK);
        }

        fprintf(pLog, "Close socket client connection with PFC\n");
        fclose(pLog);
        close(pCM1->fdClient);
        exit(EXIT_SUCCESS);
    }

    // PFC2 Pipe
    if (fork() == 0) {
        char *logPathName = malloc(1 + strlen(logPath) +
                strlen("speedPFC2.log"));
        strcpy(logPathName, logPath);
        strcat(logPathName, "speedPFC2.log");
        FILE *pLog = fopen(logPathName, "w+");

        conMeta *pCM2 = malloc(sizeof(conMeta));
        fprintf(pLog, "Open pipe client connection with PFC2\n");
        createPipeClient(pCM2, PIPE_TRANS_NAME);

        while (1) {
            //connection with pfc2
            //create log for pfc2 called: speedPFC2.log
            char *str = readInstantSpeed(pCM2->fdClient);
            fprintf(pLog, "Received %s from PFC\n", str);
            if (!strcmp(str, STOP_SIGNAL)) {
                fprintf(pLog, "\tStop signal detected on pipe\n");
                break;
            }
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
        char *logPathName = malloc(1 + strlen(logPath) +
                strlen("speedPFC3.log"));
        strcpy(logPathName, logPath);
        strcat(logPathName, "speedPFC3.log");
        FILE *pLog = fopen(logPathName, "w+");

        conMeta *pCM3 = malloc(sizeof(conMeta));

        while (1) {
            char str[255];
            do{
                pCM3->pFile = fopen(FILE_TRANS_NAME, "r");
                if (pCM3->pFile != NULL) {
                    fprintf(pLog, "Got priority on data connection file\n");
                    break;
                }
                fprintf(pLog, "Failed to get priority on connection file\n");
                sleep(CLOCK);
            } while (1);
            fgets(str, 255, pCM3->pFile);
            fprintf(pLog, "Received %s from PFC\n", str);
            fclose(pCM3->pFile);
            if (!strcmp(str, STOP_SIGNAL)) {
                fprintf(pLog, "\tStop signal detected on file\n");
                break;
            }
            sleep(CLOCK);
        }
        fprintf(pLog, "Close file client connection with PFC\n");
        fclose(pLog);
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

