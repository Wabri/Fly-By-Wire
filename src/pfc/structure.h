
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

int newRecordNMEA(PFC *, char *);

int gpgllRawElementExtractFrom(RawElement *, char *);
