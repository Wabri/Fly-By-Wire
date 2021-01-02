#include "constants.h"
#include "pfc/pfc.h"
#include "transducer/transducer.h"
#include "fman/fman.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *argv[]) {

    // Transducer
    if (fork() == 0) {
        transducer(TRANS_LOGS_PATH);
        exit(EXIT_SUCCESS);
    }

    int *pidPFCs = malloc(sizeof(int[3]));
    
    // PFC1
    pidPFCs[0] = fork();
    if (pidPFCs[0] == 0) {
        printf("pfc1: %d\n",getpid());
        pfc("PFC1", G18_PATH, PFC_LOGS_PATH, PFC_1_SENTENCE, PFC_TRANS_SOCKET);
        exit(EXIT_SUCCESS);
    }

    // PFC2
    pidPFCs[1] = fork();
    if (pidPFCs[1] == 0) {
        printf("pfc2: %d\n",getpid());
        pfc("PFC2", G18_PATH, PFC_LOGS_PATH, PFC_2_SENTENCE, PFC_TRANS_PIPE);
        exit(EXIT_SUCCESS);
    }

    // PFC3
    pidPFCs[2] = fork();
    if (pidPFCs[2] == 0) {
        printf("pfc3: %d\n",getpid());
        pfc("PFC3", G18_PATH, PFC_LOGS_PATH, PFC_3_SENTENCE, PFC_TRANS_FILE);
        exit(EXIT_SUCCESS);
    }
    
    // FMAN
    if (fork() == 0) {
        fman(pidPFCs);
    }

    wait(NULL);
    wait(NULL);
    wait(NULL);
    wait(NULL);
    wait(NULL);

    exit(EXIT_SUCCESS);
}

