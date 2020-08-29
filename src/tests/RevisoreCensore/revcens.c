// publicatore: stampa caratteri ricevuti dal censore
// censore: filtra i caratteri ricevuti dal revisore passando al pubblicatore
// tramite pipe solo i caratteri non c
// revisore: legge l'articolo e invia tramite pipe il contenuto carattere per
// carattere

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define RevCen "RCPipe"
#define CenPub "CPPipe"
#define Filter "c"
#define MessLen 1

int revisore(char *article, int messageLenght, char *pipeRevCenName);
int censore(int messageLenght, char *pipeRevCenName, char *pipeCenPubName,
            char *filterChar);

int main(int argc, char *argv[]) {

  if (fork() == 0) {
    // revisore
    exit(revisore(argv[1], MessLen, RevCen));
  } else {
    // father
    if (fork() == 0) {
      // censore
      exit(censore(MessLen, RevCen, CenPub, Filter));
    } else {
      // pubblicatore
      printf("Pubblicatore start\n");

      sleep(4);

      unlink(CenPub);
      mknod(CenPub, S_IFIFO, 0);
      chmod(CenPub, 0660);

      printf("Pipe Censore->Pubblicatore aperta\n");

      char content[1];
      int pipeCPId = open(CenPub, O_RDONLY);

      while (1) {

        int totCharRead = read(pipeCPId, content, MessLen);

        if (strcmp(content, "\0") || totCharRead == 0) {
          printf("Fine: %s", content);
          break;
        }
        printf("Pubblico: %s", content);

        printf("%s", content);
      }

      close(pipeCPId);
      unlink(CenPub);

      wait(NULL);
    }
  }

  exit(EXIT_SUCCESS);
}

int revisore(char *fileArticle, int messageLenght, char *pipeRevCenName) {

  printf("Revisore start\n");

  FILE *pfArticle = fopen(fileArticle, "r"); // open article
  char content[1];
  int pipeId;

  do {
    pipeId = open(pipeRevCenName, O_WRONLY);

    if (pipeId == -1) {
      sleep(1);
      printf("Pipe Censore->Pubblicatore risulta non aperta\n");
    }
  } while (pipeId == -1);

  printf("Revisore pronto a scrivere in pipe\n");

  while (1) {
    int iTotCharRead = fread(content, 1, messageLenght, pfArticle);
    if (iTotCharRead == 0) {
      printf("Esco: %s", content);
      break;
    }
    printf("Scrivo: %s", content);
    write(pipeId, content, messageLenght);
  }

  fclose(pfArticle);

  return EXIT_SUCCESS;
}

int censore(int messageLenght, char *pipeRevCenName, char *pipeCenPubName,
            char *filterChar) {

  printf("Censore start\n");

  unlink(pipeRevCenName);
  mknod(pipeRevCenName, S_IFIFO, 0);
  chmod(pipeRevCenName, 0660);

  printf("Pipe Revisore->Censore aperta\n");

  int pipeRCId = open(pipeRevCenName, O_RDONLY);
  int pipeCPId;
  char content[1];

  do {
    pipeCPId = open(pipeCenPubName, O_WRONLY);

    if (pipeCPId == -1) {
      printf("Pipe Censore->Pubblicatore risulta non aperta\n");
      sleep(1);
    }

  } while (pipeCPId == -1);

  printf("Censore pronto a scrivere in pipe\n");

  while (1) {

    int totCharRead = read(pipeCPId, content, MessLen);

    if (strcmp(content, "\0") || totCharRead == 0) {
      printf("Fine: %s", content);
      break;
    }
    printf("Scrivo: %s", content);

    if (strcmp(content, filterChar) == 0) {
      printf("Leggo: %s", content);
      write(pipeCPId, content, messageLenght);
    }
  }

  unlink(pipeRevCenName);

  return EXIT_SUCCESS;
}
