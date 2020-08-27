#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  printf("Start processo 1\n");
  int son1 = fork();
  if (son1 == 0) {
    // son
    while (1) {
      printf("Processo figlio %d\n", getpid());
      sleep(1);
    }
    exit(EXIT_SUCCESS);
  } else if (son1 > 0) {
    printf("Processo %d lanciato con successo\n", son1);
  }

  printf("Start processo 2\n");
  int son2 = fork();
  if (son2 == 0) {
    // son
    while (1) {
      printf("Processo figlio %d\n", getpid());
      sleep(1);
    }
    exit(EXIT_SUCCESS);
  } else if (son2 > 0) {
    printf("Processo %d lanciato con successo\n", son2);
  }

  printf("Aspetto 3 secondi\n");
  sleep(3);
  kill(son1, SIGSTOP);
  printf("Stop son: %d\n", son1);
  sleep(3);
  kill(son1, SIGCONT);
  printf("Restart son: %d\n", son1);
  sleep(3);
  kill(son1, SIGKILL);
  kill(son2, SIGKILL);
  printf("kill sons: %d, %d\n", son1, son2);

  exit(EXIT_SUCCESS);
}
