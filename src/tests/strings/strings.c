/*
 *
 * Hello world!
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void elabora1(char *pointChar);

void elabora1(char *pointChar) { printf("%s\n", pointChar); }

int main(void) {

  char c[10]; // array di caratteri

  char c1[] = {'h', 'e', 'l', 'l', 'o'}; // array di caratteri

  char str[] = {'h', 'e', 'l', 'l', 'o', '\0'}; // stringa

  char str1[] = "value of str: "; // stringa

  char *pc;
  pc = "hello:"; // stringa

  strcat(str1, str);

  elabora1(str1);

  exit(EXIT_SUCCESS);
}
