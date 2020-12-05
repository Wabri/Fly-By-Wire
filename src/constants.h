#define PFC_DEFAULT_SENTENCE "$GPGLL"
#define G18_PATH "resources/G18.txt"
#define LOGS_PATH "logs/"
#define EARTH_RADIUS_KM 6371
#define CLOCK 1

// Definition of every pfc
#define PFC_1_SENTENCE PFC_DEFAULT_SENTENCE
#define PFC_2_SENTENCE PFC_DEFAULT_SENTENCE
#define PFC_3_SENTENCE PFC_DEFAULT_SENTENCE
#define EARTH_RADIUS_M EARTH_RADIUS_KM*1000

// Connection constants
#define SOCK_PROTOCOL 0
// TODO: Is 10 a good value?
#define SOCK_MAX_CONN 10
#define SOCK_TRANS_NAME "Transducer"
