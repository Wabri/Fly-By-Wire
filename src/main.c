#include "main.h"
#include "constants.h"
#include "pfc/pfc.h"
#include "transducer/transducer.h"
#include "fman/fman.h"
#include "wes/wes.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *argv[]) {
    char* g18Path = extractG18FromArgument(argc, argv);
    int processCounter = 0;

    //FILE *pSL1;
    //do{
    //    pSL1 = fopen(g18Path, "r");
    //    if (pSL1 != NULL) {
    //        break;
    //    }
    //} while (1);

    //long status = 0;

    //do {
    //    status = ftell(pSL1);
    //    printf("%c\n", getc(pSL1));
    //    fseek(pSL1, -status, SEEK_CUR);
    //    fflush(pSL1);
    //    sleep(CLOCK);
    //}while (1);

    //exit(EXIT_SUCCESS);

    if (!isFileExistsAccess(g18Path)){
        exit(EXIT_FAILURE);
    }

    int *pidPFCs = malloc(sizeof(int[3]));

    processCounter += 1;
    pidPFCs[0] = fork();
    if (pidPFCs[0] == 0) {
        pfc(g18Path, PFC_SOCK_SENTENCE, PFC_TRANS_SOCKET);
        exit(EXIT_SUCCESS);
    }

    processCounter += 1;
    pidPFCs[1] = fork();
    if (pidPFCs[1] == 0) {
        pfc(g18Path, PFC_PIPE_SENTENCE, PFC_TRANS_PIPE);
        exit(EXIT_SUCCESS);
    }

    processCounter += 1;
    pidPFCs[2] = fork();
    if (pidPFCs[2] == 0) {
        pfc(g18Path, PFC_FILE_SENTENCE, PFC_TRANS_FILE);
        exit(EXIT_SUCCESS);
    }

    processCounter += 1;
    if (fork() == 0) {
        transducer();
        exit(EXIT_SUCCESS);
    }

    processCounter += 1;
    if (fork() == 0) {
        fman(pidPFCs);
        exit(EXIT_SUCCESS);
    }

    processCounter += 1;
    if (fork() == 0) {
        wes();
        exit(EXIT_SUCCESS);
    }

    while (processCounter) {
        wait(NULL);
        processCounter -= 1;
    }

    exit(EXIT_SUCCESS);
}

char* extractG18FromArgument(int argc, char *argv[]) {
    if (argc == 1) {
        return G18_PATH;
    } else if (argc == 2) {
        return argv[1];
    }
    return "";
}

int isFileExistsAccess(const char *filePath) {
    if (access(filePath, F_OK) == -1) {
        return 0;
    }
    return 1;
}
