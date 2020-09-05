
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

int newRecordNMEA(PFC *, char *);

int gpgllExtractFrom(GPGLL *, char *);

