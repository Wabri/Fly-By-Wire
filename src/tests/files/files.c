/*
 *
 * Hello world!
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define RECORD 10

int main(int argc, char *argv[]) {

  FILE *pfFile;
  printf("%d\n", EOF);

  /* modalità di apertura:
   * r -> apre il file in sola lettura posizionandosi all'inizio del file
   * r+ -> apre il file in lettura e scrittura posizionandosi all'inizio del
   * file w -> apre il file in sola scrittura creandolo se necessario o
   * troncandone a 0 il suo contenuto se questo esisteva già w+ -> apre il file
   * in scrittura e lettura creandolo se necessario o troncandone ... a -> apre
   * il file in aggiunta (append) creandolo se necessario o aggiungendovi dati a
   * partire alla fine posizionandosi quindi alla fine del file stesso a+ ->
   * apre il file in aggiunta e in lettura, creandolo se necessario ...
   */
  pfFile = fopen("src/tests/files/files.sh", "r");

  /* se il file è un binario, sarà necessario aggiungere b dopo la definizione
   * della modalità es: fopen("file", "rb");
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
  if (i <= 0) {
    printf("Errore in lettura\n");
  } else {
    printf("%s\n", arrayChar);
  }
  // la read dovrebbe restituire errore dato che il file è stato già letto
  i = fread(arrayChar, 1, 100, pfFile);
  if (i <= 0) {
    printf("Errore in lettura\n");
  } else {
    printf("%s\n", arrayChar);
  }
  fclose(pfFile);

  char arrayChar2[15];
  FILE *pfOUT;
  pfFile = fopen("src/tests/files/files.sh", "r");
  pfOUT = fopen("src/tests/files/files.txt", "w");
  while (1) {
    i = fread(arrayChar2, 1, 15, pfFile);
    printf("%d\n", i);
    if (i < 15) {
      printf("stop\n");
      break;
    } else {
      printf("%s\n", arrayChar2);
      fwrite(arrayChar2, 1, 15, pfOUT);
    }
  }
  fclose(pfFile);
  fclose(pfOUT);
  pfFile = fopen("src/tests/files/files.txt", "r");
  i = fread(arrayChar, 1, 100, pfFile);
  if (i <= 0) {
    printf("Errore in lettura\n");
  } else {
    printf("%s\n", arrayChar);
  }
  fclose(pfFile);

  char ac[RECORD];
  FILE *puntatoreFile;
  int iQta;
  int iPosizione1;
  int iPosizione2;

  puntatoreFile = fopen("src/tests/files/files.txt", "r+");
  while (1) {
    iPosizione1 = ftell(puntatoreFile);
    iQta = fread(ac, 1, RECORD, puntatoreFile);

    if (iQta == 0) {
      printf("something happened\n");
      break;
    }

    iPosizione2 = ftell(puntatoreFile);
    fseek(puntatoreFile, iPosizione1, SEEK_SET);

    ac[0] = '!';

    fwrite(ac, 1, iQta, puntatoreFile);

    fseek(puntatoreFile, iPosizione2 + 1, SEEK_SET);
  }

  // SEEK_SET rappresenta l'inizio del file
  // SEEK_CUR rappresenta la posizione attuale del file
  // SEEK_END rappresenta la fine del file

  fclose(puntatoreFile);

  puntatoreFile = fopen("src/tests/files/files.txt", "r+");

  iPosizione1 = ftell(puntatoreFile);
  fgets(ac, RECORD, puntatoreFile);
  printf("%s\n", ac);
  fgets(ac, RECORD, puntatoreFile);
  printf("%s\n", ac);
  fseek(puntatoreFile, iPosizione1, SEEK_SET);
  fgets(ac, RECORD, puntatoreFile);
  printf("%s\n", ac);
  fputs("replace you!", puntatoreFile);

  exit(EXIT_SUCCESS);
}
