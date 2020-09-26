
#include "structure.h"
#include "../constants.h"
#include "../utility/angles.h"
#include "../utility/string.h"
#include <math.h>
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

  if (pFile == NULL) {
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
      printf("%f\n", pPTP->traveledDistance);
      printf("%f\n", pPTP->istantSpeed);
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
    pPTP->point = pGLL;
    pPTP->traveledDistance = 0;
    pPTP->istantSpeed = 0;
  } else {
    pPTP->next = (PTP *)malloc(sizeof(PTP));
    pPTP->next->point = pGLL;
    pPTP->next->traveledDistance =
        computeDistance(pPTP->point, pPTP->next->point);
    pPTP->next->istantSpeed =
        pPTP->istantSpeed + pPTP->next->traveledDistance / CLOCK;
  }
}

float computeDistance(GLL *start, GLL *end) {
  float fDLatitude = degreesToRadiants(end->fLatitude - start->fLatitude);
  float fDLongitude = degreesToRadiants(end->fLongitude - start->fLongitude);
  float fSLatitude = degreesToRadiants(start->fLatitude);
  float fELatitude = degreesToRadiants(end->fLatitude);
  float fHa = pow(sin(fDLatitude / 2), 2) +
              pow(sin(fDLongitude / 2), 2) * cos(fSLatitude) * cos(fELatitude);
  float fHc = 2 * atan2(sqrt(fHa), sqrt(1 - fHa));
  return EARTH_RADIUS_KM * fHc;
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
