#include <sys/un.h>
typedef struct socketMetadata {
	struct sockaddr_un serAdd; // server address
	struct sockaddr* pSerAdd; // pointer to server
	struct sockaddr_un cliAdd; // client address
	struct sockaddr* pCliAdd; // pointer to client
	unsigned int serLen;
	unsigned int cliLen;
	int fdClient; //fileDescriptorClient
	int fdServer; //fileDescriptorServer
} sockMeta;

void createSocketClient(sockMeta *, char *);

void createSocketServer(sockMeta *, char *);

