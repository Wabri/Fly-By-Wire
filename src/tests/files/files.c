/*
 *
 * Hello world!
 *
 */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

  FILE *pfFile;

  printf("%d\n",EOF);

  /* modalità di apertura:
   * r -> apre il file in sola lettura posizionandosi all'inizio del file
   * r+ -> apre il file in lettura e scrittura posizionandosi all'inizio del file
   * w -> apre il file in sola scrittura creandolo se necessario o troncandone a 0 il suo contenuto se questo esisteva già
   * w+ -> apre il file in scrittura e lettura creandolo se necessario o troncandone ...
   * a -> apre il file in aggiunta (append) creandolo se necessario o aggiungendovi dati a partire alla fine posizionandosi quindi alla fine del file stesso
   * a+ -> apre il file in aggiunta e in lettura, creandolo se necessario ...
   */
  pfFile = fopen("src/tests/files/files.sh", "r");

  /* se il file è un binario, sarà necessario aggiungere b dopo la definizione della modalità
   * es: fopen("file", "rb");
   */

  int isClose = fclose(pfFile);

  if (isClose == 0) {
    printf("File chiuso con successo!\n");
  } else if (isClose == EOF) {
    printf("Errore durante la chiusura del file!\n");
  } else {
    printf("Errore sconosciuto durante la chiusura del file!\n");
  }

  char arrayChar[100];
  int i;
  pfFile = fopen("src/tests/files/files.sh", "r");

  i = fread(arrayChar, 1, 100, pfFile);

  if (i <= 0 ) {
    printf("Errore in lettura\n");
  } else {
    printf("%s\n",arrayChar);
  }
  
  exit(EXIT_SUCCESS);
}


