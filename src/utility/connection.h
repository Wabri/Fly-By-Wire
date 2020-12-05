typedef struct socketMetadata {
	struct sockaddr_un* pSerAdd; // pointer to server
	struct sockaddr_un* pCliAdd; // pointer to client
	unsigned int iLength;
	int fdClient; //fileDescriptorClient
	int fdServer; //fileDescriptorServer
} sockMeta;

int createSocketClient(sockMeta*);

void createSocketServer(sockMeta*);

