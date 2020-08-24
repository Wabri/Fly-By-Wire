#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  int fd;

  fd = open("nonesisto.txt", O_RDONLY);
  if (fd == -1) {
    printf("errno= %d\n", errno);
    perror("main");
  }

  fd = open("/", O_WRONLY);
  if (fd == -1) {
    printf("errno= %d\n", errno);
    perror("main");
  }

  fd = open("nonesisto.txt", O_RDONLY | O_CREAT, 0644);
  printf("errno= %d\n", errno);
  perror("main");
  errno=0;
  perror("main");

  exit(EXIT_SUCCESS);
}
