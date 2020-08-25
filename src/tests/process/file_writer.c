#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *argv[]) {

  if (argc > 1) {
    char content[100];
    char *sFile = argv[1];
    FILE *pFile = fopen(sFile, "r+");
    long lIFile = ftell(pFile);

    int son = fork();
    if (son < 0) {
      printf("Fork fallita!\n");
      exit(EXIT_FAILURE);
    } else if (son != 0) {
      wait(&son);
      fseek(pFile, lIFile, SEEK_SET);
      int iQuantity;
      iQuantity = fread(content, 1, 100, pFile);

      if (iQuantity == 0) {
        printf("something happened\n");
        exit(EXIT_FAILURE);
      }
      printf("%s\n", content);

    } else {
      scanf("%s", content);
      fprintf(pFile, content);
    }
  }

  exit(EXIT_SUCCESS);
}
