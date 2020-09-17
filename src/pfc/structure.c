
#include "structure.h"
#include "../utility/angles.h"
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
      if (NULL != pPTP->next) {
        pPTP = pPTP->next;
      }
      fprintf(pLog, "%d catch: %s", getpid(), sLine);
    }
    // sleep(1);
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
  pGLL->fLatitude = atof(pRawElementTemp->element);
  pRawElementTemp = pRawElementTemp->next;
  // - N Meridian
  pGLL->cMeridianDirection = pRawElementTemp->element[0];
  pRawElementTemp = pRawElementTemp->next;
  // - 00852.8469 longitude
  pGLL->fLongitude = atof(pRawElementTemp->element);
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
         pGLL->fLatitude, pGLL->cMeridianDirection, pGLL->fLongitude,
         pGLL->cParallelDirection, pGLL->iFixTaken, pGLL->sDataValid);
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
  if (pPTP->point == NULL) {
      // TODO: non entra mai qui
    pPTP->point = pGLL;
    pPTP->traveledDistance = 0;
  } else {
    pPTP->next = (PTP *)malloc(sizeof(PTP));
pPTP->next->point = pGLL;
printf("test gll %f\n", pGLL->fLatitude);
    printf("test ptp %f\n", pPTP->point->fLatitude);
    pPTP->next->traveledDistance =
        computeDistance(pPTP->point, pPTP->next->point);
  }
}

float computeDistance(GLL *start, GLL *end) {
  // https://stackoverflow.com/questions/365826/calculate-distance-between-2-gps-coordinates
  // ricordarsi di operare in metri, in input si ha 4 cifre i metri sono a 2
  // TODO: Now the big formula need to be apply
  /* float dLatitude = degreesToRadians(start->fLatitude - end->fLatitude); */
  /* float dLongitude = degreesToRadians(start->fLongitude - end->fLongitude);
   */
  float temp = degreesToRadians(30.2);
  printf("%f \n", temp);
  printf("%f \n", start->fLatitude);
  printf("%f \n", start->fLongitude);
  return 1;
}

void printPTPs(PTP *pPTP) {
  while (pPTP->point != NULL) {
    printPTP(pPTP);
    pPTP = pPTP->next;
  }
}

void printPTP(PTP *pPTP) {
  printf("Start: %d, Traveld Distance: %f\n", pPTP->point->iFixTaken,
         pPTP->traveledDistance);
}
