#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

void sigHandler(int signum);
void sigHandler2(int signum);

int main(int argc, char *argv[]) {

  int son = fork();
  if (son < 0) {
    // forkr failed
    exit(EXIT_FAILURE);
  } else if (son != 0) {
    // father
    signal(SIGCHLD, sigHandler);
    printf("Sono il padre\n");
  } else {
    // son
    printf("Sono il figlio\n");
    exit(EXIT_SUCCESS);
  }

  // Proteggere sezioni critiche dovute a CTRL-C (segnale SIGINT)

  void (*oldHandler)(int);
  printf("Posso essere stoppato da sigint\n");
  sleep(3);
  oldHandler = signal(SIGINT, SIG_IGN); // Ridireziona il segnale sigint con
                                        // il segnale ign che indica di
                                        // ignorare totalmente il segnale
  // inizio sezione critica
  printf("Non posso essere stoppato da sigint\n");
  sleep(3);
  // fine sezione critica
  signal(SIGINT, oldHandler); // Il segnale di interrupt viene riprogrammato
                              // come prima
  printf("Posso essere stoppato da sigint\n");
  sleep(3);
  printf("Ciaone\n");

  signal(SIGINT, sigHandler2);

  int son2 = fork();
  if (son2 == 0) {
    printf("Child PID %d PGRP %d waits\n", getpid(), getpgid(0));
  } else if (son2 > 0) {
    printf("Parent PID %d PGRP %d waits\n", getpid(), getpgid(0));
  } else {
    // forkr failed
    exit(EXIT_FAILURE);
  }
  pause();

  exit(EXIT_SUCCESS);
}

void sigHandler(int signum) { wait(NULL); }

void sigHandler2(int sig) {
  printf("Process %d got a %d signal\n", getpid(), sig);
}
