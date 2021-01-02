// General
#define G18_PATH "resources/G18.txt"
#define LOGS_PATH "logs/"
#define CLOCK 1

#define EARTH_RADIUS_KM 6371
#define EARTH_RADIUS_M EARTH_RADIUS_KM*1000
#define DELTA_SEC 1

// PFC
#define PFC_LOGS_PATH LOGS_PATH
#define PFC_DEFAULT_SENTENCE "$GPGLL"
#define STOP_SIGNAL "#stop"

// Transducer
#define TRANS_LOGS_PATH LOGS_PATH

// PFC1: socket
#define PFC_1_SENTENCE PFC_DEFAULT_SENTENCE
#define PFC_TRANS_SOCKET 0
#define SOCK_PROTOCOL 0
#define SOCK_TRANS_NAME "bin/Socket"

// PFC2: pipe
#define PFC_2_SENTENCE PFC_DEFAULT_SENTENCE
#define PFC_TRANS_PIPE 1
#define PIPE_TRANS_NAME "bin/Pipe"

// PFC3: file
#define PFC_3_SENTENCE PFC_DEFAULT_SENTENCE
#define PFC_TRANS_FILE 2
#define FILE_TRANS_NAME "bin/File"

