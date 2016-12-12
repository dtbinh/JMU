/*----------------------------------------------------------------------

  Demo of IPC using Message Queues: The User process

  Written By: Team-00

  1- Dr. Mohamed Aboutabl

  2- Dr. Mohamed Aboutabl

  Submitted on: 10/06/2015

----------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>

#include "message.h"
/* -------------------------------------------------------------------*/
int main ( int argc , char * argv[] )
{

  msgBuf msg1 , msg2 ;
  key_t msgQueKey ;
  int queID ;
  int msgStatus ;

  printf("This is the user process (id = %d).\t\n" , getpid() );

  /* Create / Find the message queues */
  msgQueKey = BASE_MAILBOX_NAME ;
  queID = msgget( msgQueKey , IPC_CREAT | 0600 ) ; /*rw. ... ...*/
  if ( queID < 0 ) {
    printf("Failed to create mailbox %X. Error code=%d\n"
    , msgQueKey , errno ) ;
    exit(-2) ;
  }
  else
    printf( "The user process created/found mailbox %0X with qid=%d\n"
    , msgQueKey , queID ) ;

  /* prepare a message to send to the Calculator process */
  msg1.mtype = 1 ; /* this is a "Request" message type */
  msg1.info.sender = getpid() ;
  msg1.info.num1 = 15 ; msg1.info.num2 = 6 ;
  msg1.info.operation = '*' ;


  /* Send one message to the Calculator process */
  msgStatus = msgsnd( queID , &msg1 , MSG_INFO_SIZE , 0 ) ; /* the msg flag is set to 0 */
  if ( msgStatus < 0 )
  {
    printf("Failed to send message to Calculator process on queuID %d. Error code=%d\n"
    , queID , errno ) ;
    exit(-2) ;
  }
  else
  {
    printf("\nThe following message was successfully sent to the Calculator\n" );
    printMsg( & msg1 );
  }

  /* Now, wait for a message to arrive from the Calculator process */
  printf ("\nUser is now waiting to receive result ...\n" );
  msgStatus = msgrcv( queID , &msg2 , MSG_INFO_SIZE , 2 , 0 );
  if ( msgStatus < 0 ) 
  {
    printf("Failed to receive message from Calculator process on queuID %d. Error code=%d\n"
    , queID , errno ) ;
    exit(-2) ;
  }
  else
  {
    printf("User received the following message from the Calculator:\n" );
    printMsg( & msg2 );
  }

  printf("\n" );

  /* Mission Accomplished, so destroy the message queue */
  /* could also use the command 'ipcrm -q' to do the same task */
  msgctl( queID , IPC_RMID , NULL ) ;

  return 0 ;
}
