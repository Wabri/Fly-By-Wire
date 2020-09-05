#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int newRecordNMEA(PFC *ppfc, char * sElement) {
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
    strcpy(sRecordHead, sLine);
    strtok(sRecordHead, ",");
    if (strcmp(sRecordHead, sElement) == 0) {
      break;
    }
    sleep(3);
  };
  printf("%s found: %s", sElement, sLine);
  fclose(pFile);
  return 0;
}
