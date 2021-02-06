#include <stdio.h>

typedef struct pfc
{
    char *filePath;
    char *fileLog;
} PFC;

typedef struct gll
{
    float fLatitude;         // es: Latitude 49 deg. 16.45 min.
    char cMeridianDirection; // es: North
    float fLongitude;        // es: Longitude 123 deg. 11.12 min.
    char cParallelDirection; // es: West
    unsigned int iFixTaken;  // es: Fix taken at 22:54:44 UTC
    char *sDataValid;        // es: Data valid
} GLL;

typedef struct rawElement
{
    char *element;
    struct rawElement *next;
} RawElement;

typedef struct pointToPoint
{
    GLL *point;
    float traveledDistance;
    float instantSpeed;
    struct pointToPoint *next;
} PTP;

void extractRawElements(RawElement *, char *);

void extractGLL(GLL *, RawElement *);

void addPoint(PTP *, GLL *);

float computeDistance(GLL *, GLL *);
