#include "pfcds.h"
#include "../utility/connection.h"
#include "../utility/string.h"
#include "../config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void pfcds(int *pids)
{
    char *logPathName = malloc(1 + strlen(PFCDS_LOGS_PATH) + strlen(PFCDS_LOGS));
    strcpy(logPathName, PFCDS_LOGS_PATH);
    strcat(logPathName, PFCDS_LOGS);
    FILE *logFile = fopen(logPathName, "w");
    free(logPathName);

    conMeta *pCM = malloc(sizeof(conMeta));
    createPipeClient(pCM, PIPE_PFCDS_WES);

    while (1)
    {
        char *str = readWesDatas(pCM->fdClient);
        char *signal = malloc(strlen(str));
        char *sPid = malloc(strlen(str));

        int pid = -1;

        if (!strcmp(str, PFCDS_EMERGENCY_SIGNAL))
        {
            fprintf(logFile, "Emergency signal received.\n\tStart killing all process\n");
            for (int index = 0; index < 6; index += 1)
            {
                kill(pids[index], SIGKILL);
            }
            fprintf(logFile, "\tAll process killed");
            return;
        }

        strExtrSeparator(signal, str, " ");
        strExtrInterval(
            sPid,
            str,
            strSeparatorIndex(str, ' ') + 1,
            strSeparatorIndex(str, '\0'));
        pid = atoi(sPid);

        if (kill(pid, 0) == 0)
        {
            fprintf(logFile, "Signal: %s\n\tProcess with pid %d is Alive\n", signal, pid);
        }
        else
        {
            fprintf(logFile, "Signal: %s\n\tProcess with pid %d is Dead\n", signal, pid);
        }

        int pfcDead = 0;
        for (int i = 0; i < 3; i++)
        {
            if (kill(pids[i], 0) == 0)
            {
                pfcDead += 1;
            }
        }

        if (!pfcDead)
        {
            fprintf(logFile, "No more alive pfcs.\n\tStart killing all process\n");
            for (int index = 0; index < 6; index += 1)
            {
                kill(pids[index], SIGKILL);
            }
            fprintf(logFile, "\tAll process killed");
            return;
        }

        sleep(CLOCK);
        fflush(logFile);
    }
}

char *readWesDatas(int fd)
{
    char *str = malloc(sizeof(char[64]));
    int n = read(fd, str, 16);
    return str;
}
