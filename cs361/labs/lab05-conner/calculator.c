/*----------------------------------------------------------------------

  Demo of IPC using Message Queues: The Calculator process

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

  msgBuf msg ;
  key_t msgQueKey ;
  int queID ;
  int msgStatus ;
  int result ;

  printf("This is the Calculator process (id = %d).\t\n" , getpid() );

  /* Create / Find the message queues */
  msgQueKey = BASE_MAILBOX_NAME ;
  queID = msgget( msgQueKey , IPC_CREAT | 0600 ) ; /*rw. ... ...*/
  if ( queID < 0 ) {
    printf("Failed to create mailbox %X. Error code=%d\n"
    , msgQueKey , errno ) ;
    exit(-2) ;
  }
  else
    printf( "The Calculator process created/found mailbox %X with qid=%d\n"
    , msgQueKey , queID ) ;

  /* Now, wait for a message to arrive from the User process */
  printf ("\nI am now waiting to receive request ...\n" );
  msgStatus = msgrcv( queID , &msg , MSG_INFO_SIZE , 1 , 0 );
  if ( msgStatus < 0 )
  {
    printf("Failed to receive message from User process on queuID %d. Error code=%d\n"
    , queID , errno ) ;
    exit(-2) ;
  }
  else
  {
    printf("Calculator received the following message from the User:\n" );
    printMsg( & msg );
    printf("\n");
  }

  /* prepare the result to send back to the User process */
  switch ( msg.info.operation )
  {
    case '+': result = msg.info.num1 + msg.info.num2 ;
    break ;

    case '-': result = msg.info.num1 - msg.info.num2 ;
    break ;

    case '*': result = msg.info.num1 * msg.info.num2 ;
    break ;

    default: printf("\nINVALID operation\n" );
    result = -9999 ;
  } ;

  msg.info.result = result ;
  msg.mtype = 2; /* this is a "Reply" message type */
  msg.info.sender = getpid() ;

  /* Send the result message to the User process */
  msgStatus = msgsnd( queID , &msg , MSG_INFO_SIZE , 0 ) ; /* the msg flag is set to 0 */
  if ( msgStatus < 0 )
  {
    printf("Failed to send message to User process on queuID %d. Error code=%d\n"
    , queID , errno ) ;
    exit(-2) ;
  }
  else
  {
    printf("Calculator sent the following message to the User:\n" );
    printMsg( & msg );
    printf("\n" );
  }

  printf("\n" );

  return 0 ;
}
