#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

void handler(int signum) { wait(NULL); }

int main(int argc, char *argv[]) {

  int son = fork();
  if (son < 0) {
    // forkr failed
    exit(EXIT_FAILURE);
  } else if (son != 0) {
    // father
    signal(SIGCHLD, handler);
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

  exit(EXIT_SUCCESS);
}
