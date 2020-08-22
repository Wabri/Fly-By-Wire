/* rev.c */

#include <string.h>
#include "rev.h"

void reverse(char *string1, char *string2) {
  int i = 0, j = 0, len = strlen(string1);
  for (j = len - 1; j >= 0; j--, i++) {
    string2[i] = string1[j];
  }
  string2[len] = '\0';
}
