#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

char *phrase = "Stuff this in your pipe!";

int main(int argc, char *argv[]) {

  int fd[2], bytesRead;

  char message[100];

  pipe(fd);
  if (fork() == 0) {
    // child
    close(fd[READ]);
    write(fd[WRITE], phrase, strlen(phrase) + 1);
    close(fd[READ]);
  } else {
    // fater
    close(fd[WRITE]);
    bytesRead = read(fd[READ], message, 100);
    printf("Read %d bytes: %s\n", bytesRead, message);
    close(fd[READ]);
  }

  exit(EXIT_SUCCESS);
}

