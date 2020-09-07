/*
 *
 * Hello world!
 *
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct List {
  int data;
  struct List *next;
} List;

void printList(List *l) {
  int c = 0;
  for (List *lC = l; lC != NULL && c < 10; lC = lC->next) {
    printf("valore: %d\n", lC->data);
    c++;
  }
  if (c == 10) {
    printf("Stop, to many cycles\n");
  }
}

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

  free(pi);
  pi = NULL;
  free(a);
  a = NULL;
  free(b);
  b = NULL;

  struct List lA, lB;
  lA.data = 1;
  lB.data = 3;
  lA.next = lB.next = NULL;
  printf("Stampo lA\n");
  printList(&lA);
  printf("Stampo lB\n");
  printList(&lB);

  lA.next = &lB;
  printf("Stampo lA\n");
  printList(&lA);

  lB.next = &lA;
  printf("Stampo lA\n");
  printList(&lA);

  struct temp {
    int t1;
    struct temp *next;
  };

  struct temp *y1 = malloc(sizeof(struct temp));
  struct temp *y2 = y1;
  y1->t1 = 1;
  y1->next = malloc(sizeof(struct temp)), y1 = y1->next;
  y1->t1 = 2;
  printf("%d\n", y2->t1);

  exit(EXIT_SUCCESS);
}
