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

void echoServer(int fd);
int readLine(int fd, char *str);

int main(int argc, char *argv[]) {
  signal(SIGCHLD, SIG_IGN); // kill child if death to prevent zombies

  // Creazione server
  struct sockaddr_un serverUNIXAddress; // Server address
  struct sockaddr *serverSockAddrPointer =
      (struct sockaddr *)&serverUNIXAddress;
  // Pointer to server address
  int serverLen = sizeof(serverUNIXAddress);
  int fileDescriptorServer = socket(AF_UNIX, SOCK_STREAM, DEFAULT_PROTOCOL);
  serverUNIXAddress.sun_family = AF_UNIX;
  strcpy(serverUNIXAddress.sun_path, PATH);

  // Creazione client
  struct sockaddr_un clientUNIXAddress; // Client address
  struct sockaddr *clientSockAddrPointer =
      (struct sockaddr *)&clientUNIXAddress;
  // Pointer to client address
  unsigned int clientLen = sizeof(clientUNIXAddress);
  int fileDescriptorClient = socket(AF_UNIX, SOCK_STREAM, DEFAULT_PROTOCOL);

  unlink(PATH);
  bind(fileDescriptorServer, serverSockAddrPointer, serverLen);
  listen(fileDescriptorServer,
         5); // il 5 corrisponde alla lunghezza di connessioni pendenti

  while (1) {
    fileDescriptorClient =
        accept(fileDescriptorServer, clientSockAddrPointer, &clientLen);
    if (fork() == 0) {
      echoServer(fileDescriptorClient);
      close(fileDescriptorClient);
      exit(EXIT_SUCCESS);
    } else {
      close(fileDescriptorClient);
    }
  }

  exit(EXIT_SUCCESS);
}

void echoServer(int fd) {
  char str[255];
  
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
