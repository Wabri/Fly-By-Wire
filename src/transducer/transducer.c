#include "transducer.h"
#include "../constants.h"
#include "../utility/connection.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

void transducer() {

    // TODO: Manage infinite cycle and stop signal 
    // PFC1 Socket
    conMeta *pCM1 = malloc(sizeof(conMeta));
    createSocketClient(pCM1, SOCK_TRANS_NAME);
    int result = -1;
    do {
        result = connect(pCM1->fdClient, pCM1->pSerAdd, pCM1->serLen);
        if (result == -1) {
            sleep(1);
        }
    } while (result == -1);

    readInstantSpeed(pCM1->fdClient, SOCK_TRANS_NAME);
    close(pCM1->fdClient);

    // TODO: Manage infinite cycle and stop signal 
    // PFC2 Pipe
    conMeta *pCM2 = malloc(sizeof(conMeta));
    createPipeClient(pCM2, PIPE_TRANS_NAME);
    readInstantSpeed(pCM2->fdClient, PIPE_TRANS_NAME);
    close(pCM2->fdClient);
    unlink(PIPE_TRANS_NAME);

    // TODO: Manage infinite cycle and stop signal 
    // PFC3 FILE
    conMeta *pCM3 = malloc(sizeof(conMeta));
    pCM3->pFile = fopen(FILE_TRANS_NAME, "r");
    char str[255];
    int i = fread(str, 1, 15, pCM3->pFile);
    printf("TFile:%s\n", str);
    fclose(pCM3->pFile);

    //connection with pfc1
    //create log for pfc1 called: speedPFC1.log

    //connection with pfc2
    //create log for pfc2 called: speedPFC2.log

    //connection with pfc3
    //create log for pfc3 called: speedPFC3.log

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
