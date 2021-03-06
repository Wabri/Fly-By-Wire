#include <stdio.h>

typedef struct pfc {
    char *filePath;
    char *fileLog;
} PFC;

typedef struct gll {
    float fLatitude;  // eg: Latitude 49 deg. 16.45 min.
    char cMeridianDirection; // eg: North
    float fLongitude; // eg: Longitude 123 deg. 11.12 min.
    char cParallelDirection; // eg: West
    unsigned int iFixTaken;  // eg: Fix taken at 22:54:44 UTC
    char *sDataValid;        // eg: Data valid
} GLL;

typedef struct rawElement {
    char *element;
    struct rawElement *next;
} RawElement;

typedef struct pointToPoint {
    GLL *point;
    float traveledDistance;
    float instantSpeed;
    struct pointToPoint *next;
} PTP;

void extractRawElements(RawElement *, char *);

void extractGLL(GLL *, RawElement *);

void addPoint(PTP *, GLL *);

float computeDistance(GLL *, GLL *);

