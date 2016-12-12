#include <sys/types.h>
#define MAXNAMELEN 20
typedef struct {
	long mtype ; 			/* 1: production , 2: termination */

	struct {
    pid_t sender; 		/* ID of sending process */
    int factory_ID,
        capacity,
        num_parts,
        duration,
        num_iters,
        produced,
        is_done;
	} info; 
} msgBuf ;

#define MSG_INFO_SIZE ( sizeof(msgBuf) - sizeof(long) )
#define BASE_MAILBOX_NAME 0x20

void printMsg( msgBuf *m ) ;
