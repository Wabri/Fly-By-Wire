/* pal.h */

#include "pal.h"
#include "rev.h"
#include <string.h>

int palindrome(char *str) {
  char reverseStr[100];
  reverse(str, reverseStr);
  return (strcmp(str, reverseStr) == 0);
}
