#include "connection.h"
#include "../constants.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

void createSocketClient(conMeta *pCM, char *sockName) {
    struct sockaddr_un serAdd;
    pCM->serAdd = serAdd;
    pCM->pSerAdd = (struct sockaddr *)&pCM->serAdd;
    pCM->serLen = sizeof(serAdd);
    pCM->fdClient = socket(AF_UNIX, SOCK_STREAM, SOCK_PROTOCOL);
    pCM->serAdd.sun_family = AF_UNIX;
    strcpy(pCM->serAdd.sun_path, sockName);
}

void createSocketServer(conMeta* pCM, char *sockName) {
    struct sockaddr_un serAdd;

    pCM->serAdd = serAdd;
    pCM->pSerAdd = (struct sockaddr *) &pCM->serAdd;
    pCM->serLen = sizeof(pCM->serAdd);

    struct sockaddr_un cliAdd;
    pCM->cliAdd = cliAdd;
    pCM->pCliAdd = (struct sockaddr *) &pCM->cliAdd;
    pCM->cliLen = sizeof(pCM->cliAdd);

    signal(SIGCHLD, SIG_IGN);

    pCM->fdServer = socket(AF_UNIX, SOCK_STREAM, SOCK_PROTOCOL);

    pCM->serAdd.sun_family = AF_UNIX;
    strcpy(pCM->serAdd.sun_path, sockName);

    unlink(sockName);

    int bindResult = bind(pCM->fdServer, pCM->pSerAdd, pCM->serLen);
    listen(pCM->fdServer, 1);
}

void createPipeClient(conMeta *pCM, char *pipeName) {
    unlink(pipeName);
    mknod(pipeName, S_IFIFO, 0);
    chmod(pipeName, 0660);
    pCM->fdClient = open(pipeName,O_RDONLY);
}

void createPipeServer(conMeta *pCM, char *pipeName) {
    do {
        pCM->fdServer = open(pipeName, O_WRONLY);
        if (pCM->fdServer == -1) {
            sleep(1);
        }
    } while (pCM->fdServer == -1);
}

