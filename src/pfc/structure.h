
typedef struct pfc {
  char *name;
  char *filePath;
} PFC;

typedef struct gpgll {
  float fCurrentLatitude; // eg: Latitude 49 deg. 16.45 min.
  char cMeridianDirection; // eg: North
  float fCurrentLongitude; // eg: Longitude 123 deg. 11.12 min. 
  char cParallelDirection; // eg: West
  unsigned int iFixTaken;  // eg: Fix taken at 22:54:44 UTC
  char *sDataValid; // eg: Data valid
} GPGLL;

typedef struct rawElement {
  char *element;
  struct rawElement *next;
} RawElement;

void extractRawElements(RawElement *, char *);

void extractGPGLL(GPGLL *, RawElement *);

void newRecordNMEA(PFC *, char *);

void printGPGLL(GPGLL *);
