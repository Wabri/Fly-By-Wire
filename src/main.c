#include "constants.h"
#include "pfc/pfc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *argv[]) {

  // creazione 3 processi

  printf("Hallo\n");

  // PFC1
  if (fork() == 0) {
    run("PFC1", G18_PATH, LOGS_PATH, PFC_1_SENTENCE);
    exit(EXIT_SUCCESS);
  }

  // PFC2
  if (fork() == 0) {
    run("PFC2", G18_PATH, LOGS_PATH, PFC_2_SENTENCE);
    exit(EXIT_SUCCESS);
  }

  // PFC3
  if (fork() == 0) {
    run("PFC3", G18_PATH, LOGS_PATH, PFC_3_SENTENCE);
    exit(EXIT_SUCCESS);
  }

  //
  wait(NULL);
  printf("Hallo1\n");
  wait(NULL);
  printf("Hallo2\n");
  wait(NULL);
  printf("Hallo3\n");

  exit(EXIT_SUCCESS);
}
