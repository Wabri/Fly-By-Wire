/* mod.c */

#include "pal.h"
#include <stdio.h>
#include <stdlib.h>

/*****************************************************************************/
/* Function prototypes */
void reverse(char *, char *);

/*****************************************************************************/
/* Main */

int main(int argc, char *argv[]) {
  char stringa[100];

  reverse("ciaone", stringa);
  printf("%d\n", palindrome("ciaone"));
  printf("%d\n", palindrome("yoy"));

  printf("%s\n", stringa);

  exit(EXIT_SUCCESS);
}

/*****************************************************************************/
/* Function Implementation */
