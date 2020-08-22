#include "inc.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  printf("%s\n", TEST);
  printf("%d\n", THREE);
  printf("%d\n", DOUBLE(THREE));

  int test = argv[1];

#if test == 0
  printf("compilato 1<10");
#elif test == 1
  printf("compilato 10>1000");
#else
  printf("compilato sempre");
#endif

  exit(EXIT_SUCCESS);
}
