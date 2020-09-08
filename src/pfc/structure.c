#include "structure.h"
#include "../utility/string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void newRecordNMEA(PFC *ppfc, char *sElement) {
  char sLine[255];
  char sRecordHead[255];
  FILE *pFile;
  pFile = fopen(ppfc->filePath, "r");
  if (pFile == NULL) {
    printf("Error! opening file\n");
    exit(EXIT_FAILURE);
  }
  while (1) {
    fgets(sLine, 255, pFile);
    strExtrSeparator(sRecordHead, sLine, ",");
    if (strcmp(sRecordHead, sElement) == 0) {
      RawElement *pRawElement = (RawElement *)malloc(sizeof(RawElement));
      extractRawElements(pRawElement, sLine);
      GPGLL *pGPGLL = (GPGLL *)malloc(sizeof(GPGLL));
      extractGPGLL(pGPGLL, pRawElement);
      printGPGLL(pGPGLL);
      break;
    }
    sleep(2);
  };
  // printf("%s found: %s", sElement, sLine);
  fclose(pFile);
}

void extractRawElements(RawElement *pRawElement, char *sSource) {
  int iTemp[strlen(sSource) + 1];
  int iElementCounter = 0;
  for (int i = 0; i <= strlen(sSource); i++) {
    if (sSource[i] == ',') {
      iTemp[iElementCounter++] = i;
    } else if (sSource[i] == '\0') {
      iTemp[iElementCounter++] = i;
    }
  }
  RawElement *pRawElementIterator = pRawElement;
  for (int i = 0; i < iElementCounter - 1; i++) {
    pRawElementIterator->element = malloc(sizeof(sSource));
    strExtrInterval(pRawElementIterator->element, sSource, iTemp[i] + 1,
                    iTemp[i + 1] - 1);
    if (i < iElementCounter) {
      pRawElementIterator->next = (RawElement *)malloc(sizeof(RawElement));
      pRawElementIterator = pRawElementIterator->next;
    }
    if (i == iElementCounter - 2) {
      pRawElementIterator->next = NULL;
    }
  }
}

void extractGPGLL(GPGLL *pGPGLL, RawElement *pRawElement) {
  RawElement *pRawElementTemp = pRawElement;
  // - 4424.8422 latitude
  pGPGLL->fCurrentLatitude = atof(pRawElementTemp->element);
  pRawElementTemp = pRawElementTemp->next;
  // - N Meridian
  pGPGLL->cMeridianDirection = pRawElementTemp->element[0];
  pRawElementTemp = pRawElementTemp->next;
  // - 00852.8469 longitude
  pGPGLL->fCurrentLongitude = atof(pRawElementTemp->element);
  pRawElementTemp = pRawElementTemp->next;
  // - E parallel
  pGPGLL->cParallelDirection = pRawElementTemp->element[0];
  pRawElementTemp = pRawElementTemp->next;
  // - 122230 direction
  pGPGLL->iFixTaken = atoi(pRawElementTemp->element);
  pRawElementTemp = pRawElementTemp->next;
  // - V*3B Checksum
  pGPGLL->sDataValid = pRawElementTemp->element;
}

void printGPGLL(GPGLL *pGPGLL) {
  printf("Latitude: %f, Meridian direction: %c, Longitude: %f, Parallel "
         "direction: %c, Taken: %d, DataValid: %s",
         pGPGLL->fCurrentLatitude, pGPGLL->cMeridianDirection,
         pGPGLL->fCurrentLongitude, pGPGLL->cParallelDirection,
         pGPGLL->iFixTaken, pGPGLL->sDataValid);
}
