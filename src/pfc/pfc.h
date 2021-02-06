#include "../utility/connection.h"
#include "structure.h"

void pfc(char *, char *, unsigned int);

void parseNMEA(PFC *, char *, unsigned int);

void generateConnectionWithTrans(conMeta *);

void sendDataToTrans(conMeta *, char *);

void stopConnection(conMeta *);

char *extractPFCLogName(unsigned int);
