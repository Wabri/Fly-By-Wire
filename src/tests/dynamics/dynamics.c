/*
 *
 * Hello world!
 *
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  int *pi = NULL;

  if (pi != NULL) {
    printf("Puntatore valido\n");
  } else {
    printf("Puntatore INvalido\n");
  }

  int *a = malloc(2 * sizeof(int));
  int *b = a;

  printf("%d ,%d\n", b[0], b[1]);

  *a = 12;
  a++;
  *a = 4;

  printf("%d ,%d\n", b[0], b[1]);

  a = calloc(2, sizeof(int));

  b = a;
  
  printf("%d ,%d\n", b[0], b[1]);

  // Sarebbe più corretto eseguire un cast
  // Questo perchè malloc e calloc restituiscono un puntatore void
  // Una volta creato controllare se è stata allocata memoria
  a = (int *)malloc(sizeof(int));
  if (a != NULL) {
    printf("Puntatore con allocazione di memoria valida \n");
  } else {
    printf("Puntatore con allocazione di memoria INvalida\n");
  }
  // Lo standard ANSI C non lo rende necessario 
  // quindi si può non esplicitare il cast


  exit(EXIT_SUCCESS);
}
