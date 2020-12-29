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

// Pfc Transducer connection Sockets
#define PFC_TRANS_SOCKET 0
#define SOCK_PROTOCOL 0
#define SOCK_TRANS_NAME "bin/Socket"

// Pfc Transducer connection Pipe
#define PFC_TRANS_PIPE 1
#define PIPE_TRANS_NAME "bin/Pipe"

// Pfc Transducer connection file
#define PFC_TRANS_FILE 2
#define FILE_TRANS_NAME "bin/File"
