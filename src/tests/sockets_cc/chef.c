#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#define DEFAULT_PROTOCOL 0

void writeRecipe(int fd);

int main(int argc, char *argv[]) {

  unsigned int clientLen;
  int serverFd, clientFd, serverLen;

  struct sockaddr_un serverUNIXAddress; // Server address
  struct sockaddr_un clientUNIXAddress; // Client address

  struct sockaddr *serverSockAddrPtr;   // Ptr to server address
  struct sockaddr *clientSockAddrPtr;   // Ptr to client address

  signal(SIGCHLD, SIG_IGN);

  serverSockAddrPtr = (struct sockaddr *)&serverUNIXAddress;
  serverLen = sizeof(serverUNIXAddress);

  clientSockAddrPtr = (struct sockaddr *)&clientUNIXAddress;
  clientLen = sizeof(clientUNIXAddress);

  serverFd = socket(AF_UNIX, SOCK_STREAM, DEFAULT_PROTOCOL);

  serverUNIXAddress.sun_family = AF_UNIX;
  strcpy(serverUNIXAddress.sun_path, "recipe");

  unlink("recipe");
  bind(serverFd, serverSockAddrPtr, serverLen);
  listen(serverFd, 5);

  while (1) {
    clientFd = accept(serverFd, clientSockAddrPtr, &clientLen);

    if (fork() == 0) {
      writeRecipe(clientFd);
      close(clientFd);
      exit(EXIT_SUCCESS);
    } else {
      close(clientFd);
    }
  }

  exit(EXIT_SUCCESS);
}

void writeRecipe (int fd){
  static char* line1 = "spam linea 1";
  static char* line2 = "spam linea 2, spammer";

  write(fd, line1, strlen(line1) +1);
  write(fd, line2, strlen(line2) +1);
}

