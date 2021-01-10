#ifndef _CONNECTIONH_
#define _CONNECTIONH_

#include <stdio.h>
#include <sys/un.h>

typedef struct connectionMetadata {
    unsigned int connectionType; // type of connection
	struct sockaddr_un serAdd; // server address
	struct sockaddr* pSerAdd; // pointer to server
	struct sockaddr_un cliAdd; // client address
	struct sockaddr* pCliAdd; // pointer to client
	unsigned int serLen;
	unsigned int cliLen;
	int fdClient; //fileDescriptorClient
	int fdServer; //fileDescriptorServer
    FILE *pFile;
} conMeta;

void createSocketClient(conMeta *, char *);

void createSocketServer(conMeta *, char *);

void createPipeClient(conMeta *, char *);

void createPipeServer(conMeta *, char *);

#endif
