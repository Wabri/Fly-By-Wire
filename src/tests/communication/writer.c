#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  int fd, messageLen, i;
  char message[100];
  
  sprintf(message, "Hello from PID %d", getpid());

  messageLen = strlen(message) + 1;

  do {
    fd = open("aPipe", O_WRONLY);

    if (fd == -1) sleep(1);
  } while (fd == -1);

  for (i = 1; i <=3 ; i++) {
    write(fd, message, messageLen);
    sleep(3);
  }

  close(fd);

  exit(EXIT_SUCCESS);
}

