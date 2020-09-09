#include "structure.h"
#include "../utility/string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void importNMEA(PFC *pPFC, PTP *pPointToPoint, char *sElement) {
  char sLine[255];
  char sRecordHead[255];
  FILE *pFile;
  PTP *pPTP = pPointToPoint;
  pFile = fopen(pPFC->filePath, "r");
  if (pFile == NULL) {
    // printf("Error! opening file\n");
    exit(EXIT_FAILURE);
  }
  while (1) {
    if (fgets(sLine, 255, pFile) == NULL) {
      break;
    }
    strExtrSeparator(sRecordHead, sLine, ",");
    if (strcmp(sRecordHead, sElement) == 0) {
      RawElement *pRawElement = (RawElement *)malloc(sizeof(RawElement));
      extractRawElements(pRawElement, sLine);
      GLL *pGLL = (GLL *)malloc(sizeof(GLL));
      extractGLL(pGLL, pRawElement);
      addPoint(pPTP, pGLL);
      if (pPTP->end != NULL) {
        computeDistance(pPTP);
        pPTP = pPTP->next;
      }
      // TODO: schianta qui in qualche ciclo
    }
    // sleep(1);
  };
  printf("ciao");
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

void extractGLL(GLL *pGLL, RawElement *pRawElement) {
  RawElement *pRawElementTemp = pRawElement;
  // - 4424.8422 latitude
  pGLL->fCurrentLatitude = atof(pRawElementTemp->element);
  pRawElementTemp = pRawElementTemp->next;
  // - N Meridian
  pGLL->cMeridianDirection = pRawElementTemp->element[0];
  pRawElementTemp = pRawElementTemp->next;
  // - 00852.8469 longitude
  pGLL->fCurrentLongitude = atof(pRawElementTemp->element);
  pRawElementTemp = pRawElementTemp->next;
  // - E parallel
  pGLL->cParallelDirection = pRawElementTemp->element[0];
  pRawElementTemp = pRawElementTemp->next;
  // - 122230 direction
  pGLL->iFixTaken = atoi(pRawElementTemp->element);
  pRawElementTemp = pRawElementTemp->next;
  // - V*3B Checksum
  pGLL->sDataValid = pRawElementTemp->element;
}

void printGLL(GLL *pGLL) {
  printf("Latitude: %f, Meridian direction: %c, Longitude: %f, Parallel "
         "direction: %c, Taken: %d, DataValid: %s",
         pGLL->fCurrentLatitude, pGLL->cMeridianDirection,
         pGLL->fCurrentLongitude, pGLL->cParallelDirection, pGLL->iFixTaken,
         pGLL->sDataValid);
}

void addPoint(PTP *pPTP, GLL *pGLL) {
  if (pPTP->start == NULL) {
    pPTP->start = pGLL;
  } else if (pPTP->end == NULL) {
    pPTP->end = pGLL;
  } else {
    pPTP->next = malloc(sizeof(PTP));
    pPTP->next->start = pPTP->end;
    pPTP->next->end = pGLL;
  }
}

void computeDistance(PTP *pPTP) {
  // https://stackoverflow.com/questions/365826/calculate-distance-between-2-gps-coordinates
  // ricordarsi di operare in metri, in input si ha 4 cifre i metri sono a 2
  pPTP->lenght = 1;
}

void printPTPLength(PTP *pPTP) {
  while (pPTP->start != NULL) {
    printf("Start: %f, End: %f, Lenght: %f\n", pPTP->start->fCurrentLatitude,
           pPTP->end->fCurrentLongitude, pPTP->lenght);
    pPTP = pPTP->next;
  }
}
