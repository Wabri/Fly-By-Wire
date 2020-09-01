#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define DEFAULT_PROTOCOL 0

void readRecipe(int fd);
int readLine(int fd, char *str);

int main(int argc, char *argv[]) {

  int clientFd, serverLen, result;

  struct sockaddr_un serverUNIXAddress; // Server address
  struct sockaddr *serverSockAddrPtr;   // Ptr to server address
  serverSockAddrPtr = (struct sockaddr *)&serverUNIXAddress;
  serverLen = sizeof(serverUNIXAddress);
  clientFd = socket(AF_UNIX, SOCK_STREAM, DEFAULT_PROTOCOL);
  serverUNIXAddress.sun_family = AF_UNIX;
  strcpy(serverUNIXAddress.sun_path, "recipe");

  do {
    result = connect(clientFd, serverSockAddrPtr, serverLen);
    if (result == -1) {
      sleep(1);
    }
  } while (result == -1);

  readRecipe(clientFd);
  close(clientFd);

  exit(EXIT_SUCCESS);
}

void readRecipe(int fd) {
  char str[200];
  while (readLine(fd, str)) {
    printf("%s\n", str);
  }
}

int readLine(int fd, char *str) {
  int n;
  do {
    n = read(fd, str, 1);
  } while (n > 0 && *str++ != '\0');
  return (n > 0);
}
