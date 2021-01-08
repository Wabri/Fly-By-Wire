#include "wes.h"
#include "../constants.h"
#include "../utility/string.h"
#include "../transducer/transducer.h"
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

void wes(int *pidPFCs) {

    SpeedWesPFC swpfc[3];

    swpfc[0].speedLogPath = extractTransSpeedLogName(TRANS_SPFCS_LOGS);
    swpfc[1].speedLogPath = extractTransSpeedLogName(TRANS_SPFCP_LOGS);
    swpfc[2].speedLogPath = extractTransSpeedLogName(TRANS_SPFCF_LOGS);
    for (int index = 0; index < 3; index++) {
        do{

            swpfc[index].logFile = fopen(swpfc[index].speedLogPath, "r");
            if (swpfc[index].logFile != NULL) {
                break;
            }
        } while (1);

        swpfc[index].counter = -1;
        swpfc[index].speed = -1;
        swpfc[index].filePosition = 0;
    }


    while (1) {
        // sock
        extractSpeedInfos(pidPFCs, swpfc, 0);
        // pipe
        extractSpeedInfos(pidPFCs, swpfc, 1);
        // file
        extractSpeedInfos(pidPFCs, swpfc, 2);
        // processing
        printf("%d %d %d\n", swpfc[0].counter, swpfc[1].counter, swpfc[2].counter);
        if (swpfc[0].counter == swpfc[1].counter) {
            if (swpfc[0].counter == swpfc[2].counter) {
                printf("Concordi tutti\n");
            } else {
                printf("Concordi 1 e 2\n");
            }
        } else if (swpfc[0].counter == swpfc[2].counter) {
                printf("Concordi 1 e 3\n");
        } else if (swpfc[1].counter == swpfc[2].counter) {
                printf("Concordi 2 e 3\n");
        }
        sleep(CLOCK);
    }
}


void extractSpeedInfos(int *pids, SpeedWesPFC *wes, int position) {
        char data[64];
        char temp[64];
        int tempCounter;
        int cycleDone = 0;
        while (1) {
            if (cycleDone > 2) {
                return;
            } else {
                cycleDone += 1;
            }
            fseek(wes[position].logFile, wes[position].filePosition, SEEK_SET);
            fgets(data, 64, wes[position].logFile);
            if (strlen(data) < 4) {
                sleep(CLOCK);
                continue;
            }
            strExtrSeparator(temp, data, " ");
            tempCounter = atoi(temp); 
            if (tempCounter == wes[position].counter) {
                cycleDone = 0;
                sleep(CLOCK);
                continue;
            }
            break;
        }
        wes[position].counter = tempCounter;
        strExtrInterval(
                temp, 
                data, 
                strSeparatorIndex(data, ' ') + 1, 
                strSeparatorIndex(data, '\0'));
        wes[position].speed = atof(temp);
        if (strlen(data) > 1) {
            wes[position].filePosition += strlen(data); 
        } else {
            wes[position].filePosition += 11;
        }
        rewind(wes[position].logFile);
}
