#include "connection.h"
#include "../constants.h"
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int createSocketClient(sockMeta* sM) {
    sM->iLength = sizeof(struct sockaddr_un);
    // TODO: verify length of sockaddr
    sM->pSerAdd = (struct sockaddr *)malloc(sM->iLength);
    sM->pCliAdd = (struct sockaddr *)malloc(sM->iLength);
    sM->fdClient = socket(AF_UNIX, SOCK_STREAM, SOCK_PROTOCOL);
    sM->pSerAdd->sun_family = AF_UNIX;
    strcpy(sM->pSerAdd->sun_path, SOCK_TRANS_NAME);

    // TODO: set up connection attempts
    while(1){
        if (connect(sM->fdClient, (struct sockaddr *) sM->pSerAdd, sM->iLength)) {
            sleep(1);
        } else {
            break;}
    }
    return 0;
}

void createSocketServer(sockMeta* sM) {
    sM->iLength = sizeof(struct sockaddr_un);
    // TODO: verify length of sockaddr (duplicate: see createSocketClient)
    sM->pSerAdd = (struct sockaddr *)malloc(sM->iLength);
    sM->pCliAdd = (struct sockaddr *)malloc(sM->iLength);
    sM->fdClient = socket(AF_UNIX, SOCK_STREAM, SOCK_PROTOCOL);
    sM->pSerAdd->sun_family = AF_UNIX;
    strcpy(sM->pSerAdd->sun_path, SOCK_TRANS_NAME);

    unlink(SOCK_TRANS_NAME);
    // TODO: understand how to use resutl variable
    int result = bind(sM->fdServer, (struct sockaddr *) sM->pSerAdd, sM->iLength);
    listen(sM->fdServer, SOCK_MAX_CONN);
    signal(SIGCHLD, SIG_IGN);
}
