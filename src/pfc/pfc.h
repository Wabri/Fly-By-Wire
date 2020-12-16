#include "../utility/connection.h"
#include "structure.h"

void pfc(char *, char *, char *, char *, unsigned int);

void parseNMEA(PFC *, PTP *, char *, unsigned int);

void startConnectSock(sockMeta *);

void stopConnectSock(sockMeta *);

void sendTransSock(sockMeta *, char *);
