#include "structure.h"
#include "../utility/string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int gpgllExtractFrom(GPGLL *pGPGLL, char *sSource) {
  // TODO
  return 0;
}

int newRecordNMEA(PFC *ppfc, char *sElement) {
  char sLine[255];
  char sRecordHead[255];
  FILE *pFile;
  pFile = fopen(ppfc->filePath, "r");
  if (pFile == NULL) {
    printf("Error! opening file\n");
    exit(EXIT_SUCCESS);
  }
  while (1) {
    fgets(sLine, 255, pFile);
    strExtrSeparator(sRecordHead, sLine, ",");
    if (strcmp(sRecordHead, sElement) == 0) {
      GPGLL gpgll, *pGPGLL = &gpgll;
      gpgllExtractFrom(pGPGLL, sLine);
      // TODO
      break;
    }
    sleep(2);
  };
  printf("%s found: %s", sElement, sLine);
  fclose(pFile);
  return 0;
}
