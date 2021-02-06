#include "connection.h"
#include <stdio.h>

void wes(int *);

typedef struct SpeedWesPFC
{
    char *speedLogPath;
    FILE *logFile;
    long filePosition;
    int counter;
    float speed;
} SpeedWesPFC;

int extractSpeedInfos(SpeedWesPFC *);

void sendDataToPFCDS(conMeta *, char *);
