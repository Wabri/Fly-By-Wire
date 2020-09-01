/*
 *
 * Hello world!
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum boolean { false, true };
enum fruit { apple = 7, pear, orange = 3, lemon };

struct {
  int noName;
  char *hello;
} nonRiusabile;

struct Data {
  int iGiorno;
  int iMese;
  int iAnno;
} DataInizio;

struct Data DataFine;

union Livello {
  char cLivello;
  int iLivello;
};

struct LivelloUnion {
  char cTipo;
  union {
    char cLivello;
    int iLivello;
  };
};

void stampaData(struct Data);
void (*f)(struct Data);

void stampaData(struct Data DataEntry) {
  printf("La data attuale è:\n");
  printf("\t - giorno: %d\n", DataEntry.iGiorno);
  printf("\t - mese: %d\n", DataEntry.iMese);
  printf("\t - anno: %d\n", DataEntry.iAnno);
}

int main(int argc, char *argv[]) {

  DataInizio.iGiorno = 18;
  DataInizio.iMese = 8;
  DataInizio.iAnno = 2020;

  f = stampaData;

  f(DataInizio);

  nonRiusabile.hello = "ciaone";
  nonRiusabile.noName = 12;

  printf("Questa struttura non è riusabile: \n");
  printf("\t - %s\n", nonRiusabile.hello);
  printf("\t - %d\n", nonRiusabile.noName);

  f(DataFine);

  DataFine = DataInizio;

  f(DataFine);

  struct Data DataTest = {40, 12, 3333};

  f(DataTest);

  struct Data *pData;
  
  pData = &DataTest;

  DataTest.iGiorno = 0;

  pData->iAnno = 2020;

  f(*pData);

  f(DataTest);

  union Livello LivelloCarburante;
  LivelloCarburante.iLivello = 8;

  struct LivelloUnion testStructUnion;
  testStructUnion.cTipo = 'a';

  typedef struct Data Data;

  Data DataPost, DataPost2;

  typedef struct Test {
    int iCampo;
    char cCampo;
    char sCampo[];
  } T;

  T test1, test2;

  test1.iCampo = 12;

  printf("Test campo: %d\n", test1.iCampo);

  exit(EXIT_SUCCESS);
}
