
#include <stdio.h>

void wes(int *);

typedef struct name {
    char *speedLogPath;
    FILE *logFile;
    long filePosition;
    int counter;
    float speed;
} SpeedWesPFC;

void extractSpeedInfos(int *, SpeedWesPFC *, int);
