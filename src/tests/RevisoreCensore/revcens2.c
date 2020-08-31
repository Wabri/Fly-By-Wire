// publicatore: stampa caratteri ricevuti dal censore
// censore: filtra i caratteri ricevuti dal revisore passando al pubblicatore
// tramite pipe solo i caratteri non c
// revisore: legge l'articolo e invia tramite pipe il contenuto carattere per
// carattere

#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>

#define RCPipeName "RCPipe"
#define CPPipeName "CPPipe"
#define CharFilter "c"

typedef struct PipeWithName {
  char *name;
} PWN;

int revisore(PWN *pipeRevisoreCensore, char *fileToRead);
int censore(PWN *pipeRevisoreCensore, PWN *pipeCensoreRevisore,
            char *charFilter);
int pubblicatore(PWN *pipeCensoreRevisore);

int main(int argc, char *argv[]) {

  PWN sRevisoreCensore, *pRevisoreCensore = &sRevisoreCensore;
  pRevisoreCensore->name = RCPipeName;

  PWN sCensorePubblicatore, *pCensorePubblicatore = &sCensorePubblicatore;
  pCensorePubblicatore->name = CPPipeName;

  if (fork() == 0) {
    // revisore
    printf("Revisore istanziato con successo\n");
    int exitStatus = revisore(pRevisoreCensore, argv[1]);
    exit(exitStatus);
  } else {
    if (fork() == 0) {
      // censore
      printf("Censore istanziato con successo\n");
      int exitStatus =
          censore(pRevisoreCensore, pCensorePubblicatore, CharFilter);
      exit(exitStatus);
    } else {
      // pubblicatore
      printf("Pubblicatore istanziato con successo\n");
      int exitStatus = pubblicatore(pCensorePubblicatore);
      wait(NULL);
      wait(NULL);
      exit(exitStatus);
    }
  }
}

int revisore(PWN *pipeRevisoreCensore, char *fileToRead) {

  FILE *pfFile = fopen(fileToRead, "r");
  char sRead[1];

  int fileDescriptor;
  do {
    fileDescriptor = open(pipeRevisoreCensore->name, O_WRONLY);

    if (fileDescriptor == -1)
      printf("Pipe Revisore Censore non ancora aperta\n");
    sleep(1);
  } while (fileDescriptor == -1);
  printf("Pipe Revisore Censore agganciata dal revisore\n");

  while (1) {
    int charRead = fread(sRead, 1, 1, pfFile);
    if (charRead < 1) {
      printf("stop\n");
      break;
    } else {
      // write to PRC
      write(fileDescriptor, sRead, 1);
      printf("Read: %s", sRead);

      sleep(1);
    }
  }

  fclose(pfFile);

  return EXIT_SUCCESS;
}

int censore(PWN *pipeRevisoreCensore, PWN *pipeCensoreRevisore,
            char *charFilter) {
  char sStringPipe[1] = "";
  int characterRead = 1;

  unlink(pipeRevisoreCensore->name);
  mknod(pipeRevisoreCensore->name, S_IFIFO, 0);
  chmod(pipeRevisoreCensore->name, 0660);

  int fileDescriptor = open(pipeRevisoreCensore->name, O_RDONLY);
  printf("Pipe Revisore Censore aperta dal censore\n");

  while (characterRead > 0 ) {
    printf("\n\n\ncamadonna\n\n\n");
    characterRead = read(fileDescriptor, sStringPipe, 1);
    // filtra se c altrimenti invia al pubblicatore
    printf("%c", sStringPipe[0]);
  }

  close(fileDescriptor);
  unlink(pipeRevisoreCensore->name);
  printf("Pipe Revisore Censore chiusa con successo\n");

  exit(EXIT_SUCCESS);
}

int pubblicatore(PWN *pipeCensoreRevisore) {
  printf("qui ci entri?");
  return EXIT_SUCCESS;
}
