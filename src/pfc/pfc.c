#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *argv[]) {

  // creazione 3 processi

  // PFC1
  if (fork() == 0) {
    PFC pfc1, *ppfc1 = &pfc1;
    ppfc1->name = "PFC1";
    ppfc1->filePath = "resources/G18.txt";
    printf("%s Inizializzato con successo \n", ppfc1->name);
    newRecordNMEA(ppfc1, "$GPGLL");
    exit(EXIT_SUCCESS);
  }

  // PFC1
  if (fork() == 0) {
    // son
    PFC pfc2, *ppfc2 = &pfc2;
    ppfc2->name = "PFC2";
    ppfc2->filePath = "resources/G18.txt";
    printf("%s Inizializzato con successo \n", ppfc2->name);
    newRecordNMEA(ppfc2, "$GPVTG");
    exit(EXIT_SUCCESS);
  }

  // PFC1
  if (fork() == 0) {
    // son
    PFC pfc3, *ppfc3 = &pfc3;
    ppfc3->name = "PFC3";
    ppfc3->filePath = "resources/G18.txt";
    printf("%s Inizializzato con successo \n", ppfc3->name);
    newRecordNMEA(ppfc3, "$GPGSA");
    exit(EXIT_SUCCESS);
  }

  //
  wait(NULL);
  wait(NULL);
  wait(NULL);

  exit(EXIT_SUCCESS);
}
