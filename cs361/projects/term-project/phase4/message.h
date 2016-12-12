#include <sys/types.h>
#define MAXNAMELEN 20
typedef struct {
	long mtype ; 			/* 1: production , 2: termination */

	struct {
    int factory_ID,
        capacity,
        duration,
        produce;  //amount for client to produce
	} info; 
} msgBuf ;

#define MSG_INFO_SIZE ( sizeof(msgBuf) - sizeof(long) )
#define BASE_MAILBOX_NAME 0x20
