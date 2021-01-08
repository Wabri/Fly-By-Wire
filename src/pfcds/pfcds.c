#include "pfcds.h"
#include "../utility/connection.h"
#include "../config.h"

void pfcds(void) {
    conMeta *pCM;
    createPipeClient(pCM, PIPE_PFCDS_WES);

    // TODO: replace with correct value
    while (1) {
        char *str = readInstantSpeed(pCM2->fdClient);
        fprintf(pLog, "Received %s from PFC\n", str);
        if (!strcmp(str, STOP_SIGNAL)) {
            fprintf(pLog, "\tStop signal detected on pipe\n");
            break;
        }
        fprintf(pSpeedLog, "%s\n", str);
        fflush(pSpeedLog);
        sleep(CLOCK);
    }
}

char *readInstantSpeed(int fd) {
    char *str = malloc(16);
    int n = read(fd, str, 16);
    return str;
}
