#include "pfc.h"
#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void run(char *name, char *filePath, char *logPath, char *sentence) {
    // printf("pfc: %d\n", getpid());
    PFC pfc, *ppfc = &pfc;
    PTP ptp, *pptp = &ptp;
    ppfc->name = name;
    ppfc->filePath = filePath;

    char *logPathName = malloc(1 + strlen(logPath) + strlen("log_") +
            strlen(ppfc->name) + strlen(".txt"));
    logPathName[0] = '\0';

    strcat(logPathName, logPath);
    strcat(logPathName, "log_");
    strcat(logPathName, ppfc->name);
    strcat(logPathName, ".txt");

    ppfc->fileLog = logPathName;

    importNMEA(ppfc, pptp, sentence);
}
