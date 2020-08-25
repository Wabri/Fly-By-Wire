#include "inc.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  printf("%s\n", TEST);
  printf("%d\n", THREE);
  printf("%d\n", DOUBLE(THREE));

  int test = 8;

#if test == 0
  printf("compilato 1<10\n");
#elif test == 1
  printf("compilato 10>1000\n");
#else
  printf("compilato sempre\n");
#endif

#ifdef TEST
  printf("TEST importato con successo\n");
#endif
#ifndef TEST
  printf("Non verrà stampato\n");
#endif
#undef TEST
#ifndef TEST
  printf("TEST eliminato con successo\n");
#endif

  printf("%s\n", __FILE__);
  printf("%d\n", __LINE__);
  printf("%s\n", __DATE__);
  printf("%s\n", __TIME__);
  printf("%d\n", __STDC__);

  exit(EXIT_SUCCESS);
}
