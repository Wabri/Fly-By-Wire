#include "../constants.h"
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
    //printf("pfc1: %d\n", getpid());
    PFC pfc1, *ppfc1 = &pfc1;
    PTP ptp1, *pptp1 = &ptp1;
    ppfc1->name = "PFC1";
    ppfc1->filePath = "resources/G18.txt";
    printf("%s Inizializzato con successo \n", ppfc1->name);
    importNMEA(ppfc1, pptp1, PFC_1_SENTENCE);
    printPTPLength(pptp1);
    exit(EXIT_SUCCESS);
  }

  // PFC2
  if (fork() == 0) {
    //printf("pfc2: %d\n", getpid());
    PFC pfc2, *ppfc2 = &pfc2;
    PTP ptp2, *pptp2 = &ptp2;
    ppfc2->name = "PFC2";
    ppfc2->filePath = "resources/G18.txt";
    printf("%s Inizializzato con successo \n", ppfc2->name);
    importNMEA(ppfc2, pptp2, PFC_2_SENTENCE);
    printPTPLength(pptp2);
    exit(EXIT_SUCCESS);
  }

  // PFC3
  if (fork() == 0) {
    //printf("pfc3: %d\n", getpid());
    PFC pfc3, *ppfc3 = &pfc3;
    PTP ptp3, *pptp3 = &ptp3;
    ppfc3->name = "PFC3";
    ppfc3->filePath = "resources/G18.txt";
    printf("%s Inizializzato con successo \n", ppfc3->name);
    importNMEA(ppfc3, pptp3, PFC_3_SENTENCE);
    printPTPLength(pptp3);
    exit(EXIT_SUCCESS);
  }

  //
  wait(NULL);
  wait(NULL);
  wait(NULL);

  exit(EXIT_SUCCESS);
}
