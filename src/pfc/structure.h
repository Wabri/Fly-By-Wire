
typedef struct pfc {
  char *name;
  char *filePath;
} PFC;

typedef struct gpgll {
  float fCurrentLatitude;
  char cMeridianDirection;
  float fCurrentLongitude;
  char cParallelDirection;
  char *sChecksum;
} GPGLL;

typedef struct rawElement {
  char *element;
  struct rawElement *next;
} RawElement;

void extractRawElements(RawElement *, char *);

void extractGPGLL(GPGLL *, RawElement *);

void newRecordNMEA(PFC *, char *);
