#include "main.h"
#include "config.h"
#include "pfc/pfc.h"
#include "transducer/transducer.h"
#include "fman/fman.h"
#include "wes/wes.h"
#include "pfcds/pfcds.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *argv[])
{
    char *g18Path = extractG18FromArgument(argc, argv);
    int processCounter = 0;

    if (!isFileExistsAccess(g18Path))
    {
        exit(EXIT_FAILURE);
    }

    int *pidPFCs = malloc(sizeof(int[7]));

    processCounter += 1;
    pidPFCs[0] = fork();
    if (pidPFCs[0] == 0)
    {
        pfc(g18Path, PFC_SOCK_SENTENCE, PFC_TRANS_SOCKET);
        exit(EXIT_SUCCESS);
    }

    processCounter += 1;
    pidPFCs[1] = fork();
    if (pidPFCs[1] == 0)
    {
        pfc(g18Path, PFC_PIPE_SENTENCE, PFC_TRANS_PIPE);
        exit(EXIT_SUCCESS);
    }

    processCounter += 1;
    pidPFCs[2] = fork();
    if (pidPFCs[2] == 0)
    {
        pfc(g18Path, PFC_FILE_SENTENCE, PFC_TRANS_FILE);
        exit(EXIT_SUCCESS);
    }

    processCounter += 1;
    pidPFCs[3] = fork();
    if (pidPFCs[3] == 0)
    {
        transducer();
        exit(EXIT_SUCCESS);
    }

    processCounter += 1;
    pidPFCs[4] = fork();
    if (pidPFCs[4] == 0)
    {
        fman(pidPFCs);
        exit(EXIT_SUCCESS);
    }

    processCounter += 1;
    pidPFCs[5] = fork();
    if (pidPFCs[5] == 0)
    {
        wes(pidPFCs);
        exit(EXIT_SUCCESS);
    }

    processCounter += 1;
    pidPFCs[6] = fork();
    if (pidPFCs[6] == 0)
    {
        pfcds(pidPFCs);
        exit(EXIT_SUCCESS);
    }

    while (processCounter)
    {
        wait(NULL);
        processCounter -= 1;
    }

    exit(EXIT_SUCCESS);
}

char *extractG18FromArgument(int argc, char *argv[])
{
    if (argc == 1)
    {
        return G18_PATH;
    }
    else if (argc == 2)
    {
        return argv[1];
    }
    return "";
}

int isFileExistsAccess(const char *filePath)
{
    if (access(filePath, F_OK) == -1)
    {
        return 0;
    }
    return 1;
}
