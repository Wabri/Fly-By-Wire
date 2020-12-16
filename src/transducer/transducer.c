#include "transducer.h"
#include "../constants.h"
#include "../utility/connection.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

void readInstantSpeed(int );
int readLine(int , char*);

void transducer() {

    // TODO: open server socket connection 
    sockMeta *pSM = malloc(sizeof(sockMeta));
    createSocketClient(pSM, SOCK_TRANS_NAME);

    printf("Transducer\n");


    int result;

    // TODO: Manage infinite cycle and stop signal 
    result = -1;
    do {
        result = connect(pSM->fdClient, pSM->pSerAdd, pSM->serLen);
        if (result == -1) {
            sleep(1);
        }
    } while (result == -1);

    readInstantSpeed(pSM->fdClient);
    close(pSM->fdClient);

    //connection with pfc1
    //create log for pfc1 called: speedPFC1.log

    //connection with pfc2
    //create log for pfc2 called: speedPFC2.log

    //connection with pfc3
    //create log for pfc3 called: speedPFC3.log

}

void readInstantSpeed(int fd) {

    char str[200];
    while (readLine(fd, str)) {
        printf("T:%s\n", str);
    }
}

int readLine(int fd, char *str) {
    int n;
    do {
        n = read(fd, str, 1);
    } while (n > 0 && *str++ != '\0');
    return (n > 0);
}
