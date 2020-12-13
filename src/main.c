#include "constants.h"
#include "pfc/pfc.h"
#include "utility/connection.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <wait.h>

void readRecipe(int);
int readLine(int, char*);
void writeRecipe (int);

int main(int argc, char *argv[]) {

    // client
    //if (fork() == 0) {

    //    sockMeta *pSM = malloc(sizeof(sockMeta));

    //    createSocketClient(pSM, SOCK_TRANS_NAME);

    //    int result;

    //    do {
    //        result = connect(pSM->fdClient, pSM->pSerAdd, pSM->serLen);
    //        if (result == -1) {
    //            sleep(1);
    //        }
    //    } while (result == -1);

    //    readRecipe(pSM->fdClient);
    //    close(pSM->fdClient);

    //    exit(EXIT_SUCCESS);
    //}

    //// server
    //if (fork() == 0) {

    //    sockMeta *pSM = malloc(sizeof(sockMeta));

    //    createSocketServer(pSM, SOCK_TRANS_NAME);

    //    while(1) {
    //        pSM->fdClient = accept(pSM->fdServer, pSM->pCliAdd, &(pSM->cliLen));

    //        if (fork() == 0) {
    //            writeRecipe(pSM->fdClient);
    //            close(pSM->fdClient);
    //            exit(EXIT_SUCCESS);
    //        } else {
    //            close(pSM->fdClient);
    //        }
    //    }
    //    exit(EXIT_SUCCESS);
    //}

    //exit(EXIT_SUCCESS);

    // PFC1
    if (fork() == 0) {
        pfc("PFC1", G18_PATH, LOGS_PATH, PFC_1_SENTENCE);
        exit(EXIT_SUCCESS);
    }

    // PFC2
    if (fork() == 0) {
        pfc("PFC2", G18_PATH, LOGS_PATH, PFC_2_SENTENCE);
        exit(EXIT_SUCCESS);
    }

    // PFC3
    if (fork() == 0) {
        pfc("PFC3", G18_PATH, LOGS_PATH, PFC_3_SENTENCE);
        exit(EXIT_SUCCESS);
    }

    //
    wait(NULL);
    wait(NULL);
    wait(NULL);

    exit(EXIT_SUCCESS);
}

void readRecipe(int fd) {
    char str[200];
    while (readLine(fd, str)) {
        printf("%s\n", str);
    }
}

int readLine(int fd, char *str) {
    int n;
    do {
        n = read(fd, str, 1);
    } while (n > 0 && *str++ != '\0');
    return (n > 0);
}

void writeRecipe (int fd){
    static char* line1 = "spam linea 1";
    static char* line2 = "spam linea 2, spammer";

    write(fd, line1, strlen(line1) +1);
    write(fd, line2, strlen(line2) +1);
}

