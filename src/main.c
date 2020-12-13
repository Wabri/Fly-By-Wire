#include "constants.h"
#include "pfc/pfc.h"
#include "utility/connection.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *argv[]) {

    // client
    if (fork() == 0) {
        sockMeta *pSMC = sizeof(sockMeta);
        int fp = createSocketClient(pSMC);
    }

    // server
    if (fork() == 0) {
        sockMeta *pSMS = sizeof(sockMeta);
        createSocketServer(pSMS);
    }

    exit(EXIT_SUCCESS)

    // PFC1
    if (fork() == 0) {
        run("PFC1", G18_PATH, LOGS_PATH, PFC_1_SENTENCE);
        exit(EXIT_SUCCESS);
    }

    // PFC2
    if (fork() == 0) {
        run("PFC2", G18_PATH, LOGS_PATH, PFC_2_SENTENCE);
        exit(EXIT_SUCCESS);
    }

    // PFC3
    if (fork() == 0) {
        run("PFC3", G18_PATH, LOGS_PATH, PFC_3_SENTENCE);
        exit(EXIT_SUCCESS);
    }

    //
    wait(NULL);
    wait(NULL);
    wait(NULL);

    exit(EXIT_SUCCESS);
}

