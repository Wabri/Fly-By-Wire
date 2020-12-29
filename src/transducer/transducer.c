#include "transducer.h"
#include "../constants.h"
#include "../utility/connection.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

void transducer() {

    // TODO: Manage infinite cycle and stop signal 
    // PFC1 Socket
    if (fork() == 0) {
        conMeta *pCM1 = malloc(sizeof(conMeta));
        createSocketClient(pCM1, SOCK_TRANS_NAME);
        int result = -1;
        do {
            result = connect(pCM1->fdClient, pCM1->pSerAdd, pCM1->serLen);
            if (result == -1) {
                sleep(CLOCK);
            }
        } while (result == -1);

        while (1) {
            readInstantSpeed(pCM1->fdClient, SOCK_TRANS_NAME);
            sleep(CLOCK);
        }

        close(pCM1->fdClient);
        free(pCM1);
    }

    // TODO: Manage infinite cycle and stop signal 
    // PFC2 Pipe
    if (fork() == 0) {
        conMeta *pCM2 = malloc(sizeof(conMeta));
        createPipeClient(pCM2, PIPE_TRANS_NAME);
        while (1) {
            readInstantSpeed(pCM2->fdClient, PIPE_TRANS_NAME);
            sleep(CLOCK);
        }
        close(pCM2->fdClient);
        unlink(PIPE_TRANS_NAME);
        free(pCM2);
    }

    // TODO: Manage infinite cycle and stop signal 
    // PFC3 FILE
    if (fork() == 0) {
        conMeta *pCM3 = malloc(sizeof(conMeta));
        while (1) {
            char str[255];
            do{
                pCM3->pFile = fopen(FILE_TRANS_NAME, "r");
                if (pCM3->pFile != NULL) {
                    break;
                }
                printf("File do not exists\n");
                sleep(CLOCK);
            } while (1);
            fgets(str, 255, pCM3->pFile);
            printf("T%s:%s\n", FILE_TRANS_NAME, str);
            fclose(pCM3->pFile);
            sleep(CLOCK);
        }
        fclose(pCM3->pFile);
        free(pCM3);
    }

    //connection with pfc1
    //create log for pfc1 called: speedPFC1.log

    //connection with pfc2
    //create log for pfc2 called: speedPFC2.log

    //connection with pfc3
    //create log for pfc3 called: speedPFC3.log

    wait(NULL);
    wait(NULL);
    wait(NULL);
}

void readInstantSpeed(int fd, char *test) {
    char str[200];
    while (readLine(fd, str)) {
        printf("T%s:%s\n",test, str);
    }
}

int readLine(int fd, char *str) {
    int n;
    do {
        n = read(fd, str, 1);
    } while (n > 0 && *str++ != '\0');
    return (n > 0);
}
