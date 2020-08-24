#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  int *num;
  int result;

  printf("Inserisci un numero:");
  scanf("%d", &result);
  // Il print sotto genera una doppia stampa nonostante il figlio venga invocato
  // dopo
  // printf("%d + ", result);

  int son = fork();
  if (son < 0) {
    printf("Fork fallita!\n");
    exit(EXIT_FAILURE);
  } else if (son != 0) {
    printf("%d + ", result);
    wait(&son);
    result += 10;
    printf("%d = %d\n", 10, result);
  } else {
    result += 15;
    printf("%d + ", 15);
    exit(EXIT_SUCCESS);
  }

  exit(EXIT_SUCCESS);
}
