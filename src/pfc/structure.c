#include "structure.h"
#include "../utility/string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int gpgllRawElementExtractFrom(RawElement *prGPGLL, char *sSource) {
  int iTemp[strlen(sSource) + 1];
  int iCounter = 0;
  for (int i = 0; i <= strlen(sSource); i++) {
    if (sSource[i] == ',') {
      iTemp[iCounter++] = i;
    } else if (sSource[i] == '\0') {
      iTemp[iCounter++] = i;
    }
  }
  RawElement *pRawElement = prGPGLL;
  for (int i = 0; i < iCounter; i++) {
    pRawElement->element = malloc(sizeof(sSource));
    strExtrInterval(pRawElement->element, sSource, iTemp[i] + 1,
                    iTemp[i + 1] - 1);
    //printf("%s\n", pRawElement->element);
    printf("%d\n",iCounter);
    if (i < iCounter) {
      printf("next");
      pRawElement->next = (RawElement *)malloc(sizeof(RawElement));
      pRawElement = pRawElement->next;
    }
    if (i == iCounter - 2) {
      printf("null");
      pRawElement->next = NULL;
    }
  }
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
      RawElement *prGPGLL = (RawElement *)malloc(sizeof(RawElement));
      gpgllRawElementExtractFrom(prGPGLL, sLine);
      // printf("%s\n", prGPGLL->element);
      // TODO
      break;
    }
    sleep(2);
  };
  printf("%s found: %s", sElement, sLine);
  fclose(pFile);
  return 0;
}
