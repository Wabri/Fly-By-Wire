
#include "fman.h"
#include "../constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>

void fman(int *pidPFCs) {

    time_t t;
    srand((unsigned) time(&t));

    int pfcRun = 3;
    while (pfcRun > 0) {
        if (kill(pidPFCs[pfcRun],SIGHUP)) {
            printf("%d partito \n", pidPFCs[pfcRun]);
            pfcRun -= 1;
        } else {
            printf("%d non ancora partito\n", pidPFCs[pfcRun]);
        }
        sleep(CLOCK);
    }

    while (1) {
        int r = rand() % 3;
        if (kill(pidPFCs[r],SIGHUP)) {
            printf("Scelto %d -> %d\n", r, pidPFCs[r]);
        } else {
            printf("STOPPPPPPPPPP\n");
            break;
        }
        sleep(CLOCK);
    }

    printf("fman Stopppatooooo");
}

