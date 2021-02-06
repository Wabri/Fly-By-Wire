#include "structure.h"
#include "config.h"
#include "angles.h"
#include "string.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void extractRawElements(RawElement *pRawElement, char *sSource)
{
    int iTemp[strlen(sSource) + 1];
    int iElementCounter = 0;
    for (int i = 0; i <= strlen(sSource); i++)
    {
        if (sSource[i] == ',')
        {
            iTemp[iElementCounter++] = i;
        }
        else if (sSource[i] == '\0')
        {
            iTemp[iElementCounter++] = i;
        }
    }
    RawElement *pRawElementIterator = pRawElement;
    for (int i = 0; i < iElementCounter - 1; i++)
    {
        pRawElementIterator->element = malloc(sizeof(sSource));
        strExtrInterval(pRawElementIterator->element, sSource, iTemp[i] + 1,
                        iTemp[i + 1] - 1);
        if (i < iElementCounter)
        {
            pRawElementIterator->next = (RawElement *)malloc(sizeof(RawElement));
            pRawElementIterator = pRawElementIterator->next;
        }
        if (i == iElementCounter - 2)
        {
            pRawElementIterator->next = NULL;
        }
    }
}

void extractGLL(GLL *pGLL, RawElement *pRawElement)
{
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

void addPoint(PTP *pPTP, GLL *pGLL)
{
    if (pPTP->point == NULL)
    {
        pPTP->point = pGLL;
        pPTP->traveledDistance = 0;
        pPTP->instantSpeed = 0;
    }
    else
    {
        pPTP->next = (PTP *)malloc(sizeof(PTP));
        pPTP->next->point = pGLL;
        pPTP->next->traveledDistance =
            computeDistance(pPTP->point, pPTP->next->point);
        pPTP->next->instantSpeed =
            pPTP->instantSpeed + pPTP->next->traveledDistance / DELTA_SEC;
    }
}

float computeDistance(GLL *start, GLL *end)
{
    float fDLatitude = degreesToRadiants(end->fLatitude - start->fLatitude);
    float fDLongitude = degreesToRadiants(end->fLongitude - start->fLongitude);
    float fSLatitude = degreesToRadiants(start->fLatitude);
    float fELatitude = degreesToRadiants(end->fLatitude);
    float fHa = pow(sin(fDLatitude / 2), 2) +
                pow(sin(fDLongitude / 2), 2) * cos(fSLatitude) * cos(fELatitude);
    float fHc = 2 * atan2(sqrt(fHa), sqrt(1 - fHa));
    return EARTH_RADIUS_KM * fHc;
}
