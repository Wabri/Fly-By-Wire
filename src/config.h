// General
#define G18_PATH "resources/G18.txt"
#define LOGS_PATH "log/"
#define CLOCK 1

// Math
#define EARTH_RADIUS_KM 6371
#define EARTH_RADIUS_M EARTH_RADIUS_KM*1000
#define DELTA_SEC 1

// PFC
#define PFC_LOGS_PATH LOGS_PATH
#define PFC_DEFAULT_SENTENCE "$GPGLL"
#define STOP_SIGNAL "#stop"
#define DEFAULT_BIAS 0

// Transducer
#define TRANS_LOGS_PATH LOGS_PATH
#define TRANS_SPFCS_LOGS "speedPFC1.log"
#define TRANS_SPFCP_LOGS "speedPFC2.log"
#define TRANS_SPFCF_LOGS "speedPFC3.log"
#define TRANS_SOCK_LOGS "Trans1.log"
#define TRANS_PIPE_LOGS "Trans2.log"
#define TRANS_FILE_LOGS "Trans3.log"

// FMAN
#define FMAN_LOGS_PATH LOGS_PATH
#define FMAN_FAILURE_LOGS "failures.log"
#define FMAN_PROB_STOP .3
#define FMAN_PROB_INT .0001
#define FMAN_PROB_CONT .2
#define FMAN_PROB_USER .1

// WES
#define WES_LOGS_PATH LOGS_PATH
#define WES_LOGS "status.log"

// PFC1: socket
#define PFC_SOCK_LOG "PFC1.log"
#define PFC_SOCK_SENTENCE PFC_DEFAULT_SENTENCE
#define PFC_TRANS_SOCKET 0
#define SOCK_PROTOCOL 0
#define SOCK_TRANS_NAME "tmp/Socket"

// PFC2: pipe
#define PFC_PIPE_LOG "PFC2.log"
#define PFC_PIPE_SENTENCE PFC_DEFAULT_SENTENCE
#define PFC_TRANS_PIPE 1
#define PIPE_TRANS_NAME "tmp/Pipe"

// PFC3: file
#define PFC_FILE_LOG "PFC3.log"
#define PFC_FILE_SENTENCE PFC_DEFAULT_SENTENCE
#define PFC_TRANS_FILE 2
#define FILE_TRANS_NAME "tmp/File"

