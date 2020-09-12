
typedef struct pfc {
  char *name;
  char *filePath;
  char *fileLog;
} PFC;

typedef struct gll {
  float fCurrentLatitude;  // eg: Latitude 49 deg. 16.45 min.
  char cMeridianDirection; // eg: North
  float fCurrentLongitude; // eg: Longitude 123 deg. 11.12 min.
  char cParallelDirection; // eg: West
  unsigned int iFixTaken;  // eg: Fix taken at 22:54:44 UTC
  char *sDataValid;        // eg: Data valid
} GLL;

typedef struct rawElement {
  char *element;
  struct rawElement *next;
} RawElement;

typedef struct pointToPoint {
  GLL *start;
  GLL *end;
  float lenght;
  struct pointToPoint *next;
} PTP;

void importNMEA(PFC *, PTP *, char *);

void extractRawElements(RawElement *, char *);

void extractGLL(GLL *, RawElement *);

void printGLL(GLL *);

void printPFC(PFC *);

void addPoint(PTP *, GLL *);

void computeDistance(PTP *);

void printPTPLength(PTP *);
