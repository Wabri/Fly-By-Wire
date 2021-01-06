#include "wes.h"
#include "../constants.h"
#include "../utility/string.h"
#include "../transducer/transducer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

void wes() {

    char *speedLogPath = extractTransSpeedLogName(TRANS_SPFCF_LOGS);
    FILE *pSL1;
    do{
        pSL1 = fopen(speedLogPath, "r");
        if (pSL1 != NULL) {
            break;
        }
    } while (1);

    int counter = -1;
    float speed = -1;

    long fileTell = 0;

    while (1) {
        char data[64];
        char temp[64];
        fseek(pSL1, fileTell, SEEK_SET);
        fgets(data, 64, pSL1);
        strExtrSeparator(temp, data, " ");
        int tempCounter = atoi(temp); 
        if (tempCounter == counter) {
            continue;
        }
        counter = tempCounter;
        strExtrInterval(
                temp, 
                data, 
                strSeparatorIndex(data, ' ') + 1, 
                strSeparatorIndex(data, '\0'));
        speed = atof(temp);
        fileTell += 10;
        do {
            tempCounter /= 10;
            fileTell ++;
        } while(tempCounter != 0);
        printf("%ld\n",strlen(data));
        printf("fileTell: %ld\n", fileTell);
        printf("tempCounter: %d\n", tempCounter);
        printf("counter: %d\n", counter);
        printf("wes: %s\n", data);
        printf("speed wes: %f\n", speed);
        printf("wes at: %d\n", tempCounter);
        rewind(pSL1);
        sleep(CLOCK);
    }


}
