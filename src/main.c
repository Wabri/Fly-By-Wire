#include "constants.h"
#include "pfc/pfc.h"
#include "transducer/transducer.h"
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

    // Transducer
    if (fork() == 0) {
        transducer();
        exit(EXIT_SUCCESS);
    }

    // PFC1
    if (fork() == 0) {
        pfc("PFC1", G18_PATH, LOGS_PATH, PFC_1_SENTENCE);
        exit(EXIT_SUCCESS);
    }

    // PFC2
    //if (fork() == 0) {
    //    pfc("PFC2", G18_PATH, LOGS_PATH, PFC_2_SENTENCE);
    //    exit(EXIT_SUCCESS);
    //}

    // PFC3
    //if (fork() == 0) {
    //    pfc("PFC3", G18_PATH, LOGS_PATH, PFC_3_SENTENCE);
    //    exit(EXIT_SUCCESS);
    //}

    //
    //wait(NULL);
    //wait(NULL);
    wait(NULL);
    wait(NULL);

    exit(EXIT_SUCCESS);
}


