
#include "structure.h"
#include "../utility/string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void importNMEA(PFC *pPFC, PTP *pPointToPoint, char *sElement) {
  char sLine[255];
  char sRecordHead[255];
  FILE *pFile, *pLog;
  PTP *pPTP = pPointToPoint;
  pFile = fopen(pPFC->filePath, "r");
  pLog = fopen(pPFC->fileLog, "w+");

  if (pFile == NULL || pFile == NULL) {
    // printf("Error! opening file\n");
    exit(EXIT_FAILURE);
  }

  while (fgets(sLine, sizeof(sLine), pFile) != NULL) {
    strExtrSeparator(sRecordHead, sLine, ",");
    fprintf(pLog, "%d compare %s with  %s\n", getpid(), sElement, sRecordHead);
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
      fprintf(pLog, "%d catch: %s\n", getpid(), sLine);
      // TODO: c'è un problema nella scrittura sul log
    }
    //sleep(1);
  };

  fclose(pFile);
  fclose(pLog);
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

void printPFC(PFC *pPFC) {
  printf("Name: %s\n File Path: %s\n File Logs: %s\n", pPFC->name,
         pPFC->filePath, pPFC->fileLog);
}

void fprintPFC(FILE *pFile, PFC *pPFC) {
  fprintf(pFile, "Name: %s\n", pPFC->name);
  fprintf(pFile, "File Path: %s\n", pPFC->filePath);
  fprintf(pFile, "File Logs: %s\n", pPFC->fileLog);
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
