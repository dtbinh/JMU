#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/shm.h>
#include <sys/stat.h>

#include "operator.h"

int
main( int argc , char *argv[] )
{
  int shmid ;
  key_t shmkey;
  int shmflg ;
  shared_data *p;

  shmkey = SHMEM_KEY ;
  shmflg = IPC_CREAT | S_IRUSR | S_IWUSR ;

  shmid = shmget( shmkey , SHMEM_SIZE , shmflg ) ;
  if ( shmid == -1 )
  {
    printf("\nFailed to create/find shared memory \"0x%X\". errno=%d\n", shmkey , errno );  
    perror("Reason");
    exit(-1) ; 
  }

  p = (shared_data *) shmat( shmid , NULL , 0 );
  if ( p == (shared_data *) -1 )
  {
    printf ("\nFailed to attach shared memory id=%d\n" , shmid );
    perror("Reason");
    exit(-1) ;
  }

  while (1)
  {
    sem_wait(& (p->busFullyLoaded) );
    printf("Driver: Bus is now moving\n");
    sem_post( &(p->busMoving) );
  }

  /*
  // wait for client
  printf("Server now waits for client\n");
  if( sem_wait( & (p->client) ) )  
  {
    perror("Failed to wait for client's semaphore ") ;
    exit(-1) ;       
  }

  printf("Server now wakes up\n");

  p->d2 = p->d1 + 1;
  if( sem_post( & (p->server) ) )  // server is done
  {
    perror("Failed to post server's semaphore ") ;
    exit(-1) ;       
  }
  printf("Server posted its semaphore\n");

  shmdt( p ) ;
  shmctl( shmid , IPC_RMID , NULL );
  printf ("Server --  Goodbye\n");
  */

  return 0;
}
