#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *argv[]) {

  int result = 0;

  printf("Inserisci un numero:");
  scanf("%d", &result);
  printf("%d +", result);

  int son = fork();
  if (son < 0) {
    printf("Fork fallita!\n");
    exit(EXIT_FAILURE);
  } else if (son != 0) {
    wait(&son);
    result += 10;
    printf(" %d = %d\n", 10, result);
  } else {
    result += 15;
    printf(" %d = %d\n", 15, result);
    exit(EXIT_SUCCESS);
  }

  exit(EXIT_SUCCESS);
}
