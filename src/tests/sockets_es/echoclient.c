#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#define DEFAULT_PROTOCOL 0
#define PATH "echos"

void printEcho(int fd);

int main(int argc, char *argv[]) {

  int clientFd = socket(AF_UNIX, SOCK_STREAM, DEFAULT_PROTOCOL), result;

  // Creazione server
  struct sockaddr_un serverUNIXAddress; // Server address
  struct sockaddr *serverSockAddrPointer =
      (struct sockaddr *)&serverUNIXAddress;
  // Pointer to server address
  int serverLen = sizeof(serverUNIXAddress);
  serverUNIXAddress.sun_family = AF_UNIX;
  strcpy(serverUNIXAddress.sun_path, PATH);

  do {
    result = connect(clientFd, serverSockAddrPointer, serverLen);
    if (result == -1) {
      sleep(1);
    }
  } while (result == -1);

  printEcho(clientFd);
  close(clientFd);

  exit(EXIT_SUCCESS);
}

void printEcho(int fd) {
  char line[255];
  printf("Scrivi qualcosa: ");
  scanf("%[^\n]", line);

  write(fd, line, strlen(line) + 1);
  printf("\n");
}
