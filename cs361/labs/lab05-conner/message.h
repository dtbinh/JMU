#include <sys/types.h>

#define MAXNAMELEN 20

typedef struct {
  long mtype ; /* 1: request , 2: reply */
  struct {
    pid_t sender ; /* ID of sending process */
    int num1, num2 ; /* two operands */
    char operation ; /* arithmetic operation '+' , '-' , '*' */
    int result ; /* result of num1 operation num2 */
  } info ;
} msgBuf ;

#define MSG_INFO_SIZE ( sizeof(msgBuf) - sizeof(long) )

#define BASE_MAILBOX_NAME 0x20

void printMsg( msgBuf *m ) ;

