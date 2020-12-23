#include "constants.h"
#include "pfc/pfc.h"
#include "transducer/transducer.h"
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
        transducer();
        exit(EXIT_SUCCESS);
    }

    // PFC1
    if (fork() == 0) {
        pfc("PFC1", G18_PATH, LOGS_PATH, PFC_1_SENTENCE, PFC_TRANS_SOCKET);
        exit(EXIT_SUCCESS);
    }

    // TODO: pfc with pipe
    // PFC2
    if (fork() == 0) {
        pfc("PFC2", G18_PATH, LOGS_PATH, PFC_2_SENTENCE, PFC_TRANS_PIPE);
        exit(EXIT_SUCCESS);
    }

    // TODO: pfc with file
    // PFC3
    if (fork() == 0) {
        pfc("PFC3", G18_PATH, LOGS_PATH, PFC_3_SENTENCE, PFC_TRANS_FILE);
        exit(EXIT_SUCCESS);
    }

    wait(NULL);
    wait(NULL);
    wait(NULL);
    wait(NULL);

    exit(EXIT_SUCCESS);
}

