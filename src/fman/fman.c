#include "fman.h"
#include "../constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>

void fman(int *pidPFCs) {

    int fmanStop = 3;
    time_t t;
    srand((unsigned) time(&t));

    char *logPath = malloc(1 + strlen(FMAN_LOGS_PATH) +
            strlen(FMAN_FAILURE_LOGS));
    strcpy(logPath, FMAN_LOGS_PATH);
    strcat(logPath, FMAN_FAILURE_LOGS);
    FILE *pLog = fopen(logPath, "w+");

    while (fmanStop) {
        int selectedPFC = randRange(3);
        if (kill(pidPFCs[selectedPFC],0) == 0) {
            if (randPercent() <= FMAN_PROB_STOP) {
                fprintf(pLog, "STOP PFC%d with pid %d\n", selectedPFC + 1, pidPFCs[selectedPFC]);
                kill(pidPFCs[selectedPFC], SIGSTOP);
            }
            if (randPercent() <= FMAN_PROB_INT) {
                fprintf(pLog, "INT PFC%d with pid %d\n", selectedPFC + 1, pidPFCs[selectedPFC]);
                kill(pidPFCs[selectedPFC], SIGINT);
            }
            if (randPercent() <= FMAN_PROB_CONT) {
                fprintf(pLog, "CONT PFC%d with pid %d\n", selectedPFC + 1, pidPFCs[selectedPFC]);
                kill(pidPFCs[selectedPFC], SIGCONT);
            }
            if (randPercent() <= FMAN_PROB_USER) {
                fprintf(pLog, "USER PFC%d with pid %d\n", selectedPFC, pidPFCs[selectedPFC]);
                kill(pidPFCs[selectedPFC], SIGUSR1);
            }
        } else {
            fmanStop = 0;
            for (int i = 0; i < 3; i++) {
                if (kill(pidPFCs[selectedPFC],0) == 0) {
                    fmanStop += 1;
                }
            }
        }
        fflush(pLog);
        sleep(CLOCK);
    }
    fprintf(pLog, "No more PFC alive\n\tStop running FMAN\n");
    fclose(pLog);
}

double randPercent() {
    time_t seed;
    srand((unsigned) time(&seed));
    return ((double)rand() / (double)RAND_MAX);
}

int randRange(int range) {
    time_t seed;
    srand((unsigned) time(&seed));
    return rand() % range;
}

