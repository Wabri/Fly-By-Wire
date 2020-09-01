/*
 *
 * Hello world!
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int (*f)(int, int);

int prodotto(int a, int b) { return a * b; }
int somma(int a, int b) { return a + b; }

int main(int argc, char *argv[]) {
  printf("Il programma si chiama %s\n", argv[0]);
  printf("I suoi argomenti sono:\n");
  for (int i = 1; i < argc; i++) {
    printf("\t - argomento %d contenuto %s\n", i, argv[i]);
  }

  f = prodotto;

  printf("prodotto tra 2 elementi: %d * %d = %d\n", 12, 13, f(12, 13));

  f = somma;

  printf("somma tra 2 elementi: %d + %d = %d\n", 12, 13, f(12, 13));

  exit(EXIT_SUCCESS);
}
