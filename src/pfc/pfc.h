#include "../utility/connection.h"
#include "structure.h"

void pfc(char *, char *, char *, char *, unsigned int);

void parseNMEA(PFC *, PTP *, char *, unsigned int);

void generateConnectionWithTrans(conMeta *);

void sendDataToTrans(conMeta *, char *);

void stopConnection(conMeta *);

