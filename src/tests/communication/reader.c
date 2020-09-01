#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int readLine(int fd, char *str);

int main(int argc, char *argv[]) {
  int fd;
  char str[100];

  unlink("aPipe");
  mknod("aPipe", S_IFIFO, 0);
  chmod("aPipe", 0660);

  fd = open("aPipe", O_RDONLY);
  while (readLine(fd, str)) {
    printf("%s\n", str);
  }

  close(fd);
  unlink("aPipe");

  exit(EXIT_SUCCESS);
}

int readLine(int fd, char *str) {
  int n;

  do {
    n = read(fd, str, 1);
  } while (n > 0 && *str++ != '\0');

  return (n > 0);
}
