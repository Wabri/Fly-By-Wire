#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *argv[]) {

  if (argc > 1) {
    char content[100];
    char *sFile = argv[1];

    printf("Inserisci una stringa: ");
    scanf("%s", content);

    int son = fork();
    if (son < 0) {
      printf("Fork fallita!\n");
      exit(EXIT_FAILURE);
    } else if (son != 0) {
      wait(&son);
      FILE *pFile = fopen(sFile, "r");
      int iQuantity;
      iQuantity = fread(content, 1, 100, pFile);

      if (iQuantity == 0) {
        printf("something happened\n");
        exit(EXIT_FAILURE);
      }

      printf("Stringa letta dal padre: %s\n", content);

    } else {
      FILE *pFile = fopen(sFile, "w");
      fwrite(content, 1, 100, pFile);
      printf("Stringa scritta dal figlio: %s\n", content);
      exit(EXIT_SUCCESS);
    }
  }

  exit(EXIT_SUCCESS);
}
