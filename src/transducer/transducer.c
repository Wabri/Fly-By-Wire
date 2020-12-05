#include "transducer.h"
#include "../utility/connection.h"
#include <stdio.h>
#include <stdlib.h>

void transducer() {

    // TODO: open server socket connection 
    sockMeta* pSM = malloc(sizeof(sockMeta));
    createSocketServer(pSM);

    //connection with pfc1
    //create log for pfc1 called: speedPFC1.log

    //connection with pfc2
    //create log for pfc2 called: speedPFC2.log

    //connection with pfc3
    //create log for pfc3 called: speedPFC3.log

}
