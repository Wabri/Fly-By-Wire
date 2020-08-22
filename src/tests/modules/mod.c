/* mod.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************************************************************/
/* Function prototypes */
void reverse(char *, char *);

/*****************************************************************************/
/* Main */

int main(int argc, char *argv[]) {
  char stringa[100];

  reverse("ciaone", stringa);

  printf("%s\n", stringa);

  exit(EXIT_SUCCESS);
}

/*****************************************************************************/
/* Function Implementation */

void reverse(char *string1, char *string2) {
  int i = 0, j = 0, len = strlen(string1);
  for (j = len - 1; j >= 0; j--, i++) {
    string2[i] = string1[j];
  }
  string2[len] = '\0';
}
