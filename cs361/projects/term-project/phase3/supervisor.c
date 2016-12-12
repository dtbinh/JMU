#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>

#include "shmem.h"
#include "message.h"

int main( int argc , char *argv[] )
{
	int shmid, shmflg, queID, msgStatus, lines_active;
	key_t shmkey, msgQueKey;
	shared_data *p;
	msgBuf msg;

	shmkey = SHMEM_KEY ;
	shmflg = IPC_CREAT | S_IRUSR | S_IWUSR  /* | IPC_EXCL */ ;

	shmid = shmget( shmkey , SHMEM_SIZE , shmflg );

	if (shmid == -1)
	{
		printf("\nFailed to create/find shared memory '0x%X'.\n", shmkey );
		perror("Reason:");
		exit(-1);
	}

	p = (shared_data *) shmat( shmid , NULL , 0 );
	if (p == (shared_data *) -1)
	{
		printf ("\nFailed to attach shared memory id=%d\n" , shmid );
		perror("Reason:");
		exit(-1) ;
	} 
  
  /* Create / Find the message queues */
  msgQueKey = BASE_MAILBOX_NAME ;
  queID = msgget( msgQueKey , IPC_CREAT | 0600 ) ; /*rw. ... ...*/
  if ( queID < 0 )
  {
    printf("Failed to create mailbox %X. Error code=%d\n", msgQueKey , errno ) ;
    exit(-2) ;
  }
  
  lines_active = atoi(argv[1]);

  while (0 < lines_active)
  {
    //printf("LINES ACTIVE: %d\n", lines_active);
    /* now, wait for a message to arrive from the user process */
    msgStatus = msgrcv( queID , &msg , MSG_INFO_SIZE , 1 , 0 );
    if ( msgStatus < 0 )
    {
      printf("failed to receive message from user process on queuid %d. error code=%d\n"
          , queID , errno ) ;
      sleep(3);
      exit(-2) ;
    }

    if (msg.info.is_done == 1)
    {
      lines_active--;
      printf("Factory ID: %d Total iterations: %d Total parts produced: %d\n", msg.info.factory_ID, msg.info.num_iters, msg.info.produced);
    }
    else 
    {
      p->total += msg.info.num_parts;
      p->num_iters++;
      printf("Factory ID: %d Capacity: %d Parts produced: %d Duration: %d\n",
          msg.info.factory_ID, msg.info.capacity, msg.info.num_parts, msg.info.duration);
    }
  }


	if (sem_post(&(p->factory_lines_finished)))
  {
    perror("Failed to post factory_lines_finished semaphore");
    exit(-1);
  }

	if (sem_wait(&(p->print_aggregates)))
  {
    perror("Failed to post factory_lines_finished semaphore");
    exit(-1);
  }

	printf("\nTotal Items Produced: %d\n", p->total);
  sleep(5);

	return 0;
}
