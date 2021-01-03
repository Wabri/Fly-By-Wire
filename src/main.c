#include "main.h"
#include "constants.h"
#include "pfc/pfc.h"
#include "transducer/transducer.h"
#include "fman/fman.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *argv[]) {

    int *pidPFCs = malloc(sizeof(int[3]));

    char* g18Path = extractFromArgument(argc, argv);

    if (!isFileExistsAccess(g18Path)){
        printf("g18 file not exists: %s\n", g18Path);
        exit(EXIT_FAILURE);
    }

    printf("g18 file: %s\n", g18Path);
    
    pidPFCs[0] = fork();
    if (pidPFCs[0] == 0) {
        pfc(G18_PATH, PFC_SOCK_SENTENCE, PFC_TRANS_SOCKET);
        exit(EXIT_SUCCESS);
    }

    pidPFCs[1] = fork();
    if (pidPFCs[1] == 0) {
        pfc(G18_PATH, PFC_PIPE_SENTENCE, PFC_TRANS_PIPE);
        exit(EXIT_SUCCESS);
    }

    pidPFCs[2] = fork();
    if (pidPFCs[2] == 0) {
        pfc(G18_PATH, PFC_FILE_SENTENCE, PFC_TRANS_FILE);
        exit(EXIT_SUCCESS);
    }

    if (fork() == 0) {
        transducer();
        exit(EXIT_SUCCESS);
    }
    
    if (fork() == 0) {
        fman(pidPFCs);
        exit(EXIT_SUCCESS);
    }

    wait(NULL);
    wait(NULL);
    wait(NULL);
    wait(NULL);
    wait(NULL);

    exit(EXIT_SUCCESS);
}

char* extractFromArgument(int argc, char *argv[]) {
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
