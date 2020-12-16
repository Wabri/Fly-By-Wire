#include "connection.h"
#include "../constants.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void createSocketClient(sockMeta *pSM, char *sockName) {
    struct sockaddr_un serAdd;
    pSM->serAdd = serAdd;
    pSM->pSerAdd = (struct sockaddr *)&pSM->serAdd;
    pSM->serLen = sizeof(serAdd);
    pSM->fdClient = socket(AF_UNIX, SOCK_STREAM, SOCK_PROTOCOL);
    pSM->serAdd.sun_family = AF_UNIX;
    strcpy(pSM->serAdd.sun_path, sockName);
}

void createSocketServer(sockMeta* pSM, char *sockName) {
    struct sockaddr_un serAdd;

    pSM->serAdd = serAdd;
    pSM->pSerAdd = (struct sockaddr *) &pSM->serAdd;
    pSM->serLen = sizeof(pSM->serAdd);

    struct sockaddr_un cliAdd;
    pSM->cliAdd = cliAdd;
    pSM->pCliAdd = (struct sockaddr *) &pSM->cliAdd;
    pSM->cliLen = sizeof(pSM->cliAdd);

    signal(SIGCHLD, SIG_IGN);

    pSM->fdServer = socket(AF_UNIX, SOCK_STREAM, SOCK_PROTOCOL);

    pSM->serAdd.sun_family = AF_UNIX;
    strcpy(pSM->serAdd.sun_path, sockName);

    unlink(sockName);

    int bindResult = bind(pSM->fdServer, pSM->pSerAdd, pSM->serLen);
    listen(pSM->fdServer, 1);
}
