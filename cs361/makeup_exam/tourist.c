#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/shm.h>
#include <sys/stat.h>

#include "operator.h"

int
main( int argc , char *argv[] )
{
  int ii;
  int shmid ;
  key_t shmkey;
  int shmflg ;
  shared_data *p;
  int touristId;

  shmkey = SHMEM_KEY ;
  shmflg = IPC_CREAT | S_IRUSR | S_IWUSR  /* | IPC_EXCL */ ;

  shmid = shmget( shmkey , SHMEM_SIZE , shmflg ) ;
  if ( shmid == -1 )
  {
    printf("\nFailed to create/find shared memory '0x%X'.\n", shmkey );
    perror("Reason: ");
    exit(-1) ;    
  }

  p = (shared_data *) shmat( shmid , NULL , 0 );
  if ( p == (shared_data *) -1 )
  {
    printf ("\nFailed to attach shared memory id=%d\n" , shmid );
    perror("Reason: ");
    exit(-1) ;
  } 
  
  for (ii = 0; ii < 3; ii++);
  {
    touristId = atoi(argv[0]);
    printf("Tourist %d: I am shopping\n", touristId);
    sleep(rand() % 3 + 1);
    sem_wait( &(p->availSeats) );
    p->onboard++;
    printf("Tourist %d: I am on board the bus\n", touristId);

    while ( p->onboard < 3 ); // wait until bus is fully loaded
    sem_post( &(p->busFullyLoaded) );
    printf("Tourist %d: Hey Driver! Let's Tour the City!\n", touristId);
    sem_wait( &(p->busMoving) );
    printf("Tourist %d: The Wheels on the Bus go Round and Round!\n", touristId);
  }


  /*
  // Initialize both rendezvous semaphores in the shared memory
  if( sem_init( & (p->client) , 1 , 0 )   )
  {
    perror("Failed to init client's semaphore ");
    exit(-1) ;     
  }
  if( sem_init( & (p->server) , 1 , 0 )   )
  {
    perror("Failed to init server's semaphore ") ;
    exit(-1) ;    
  }

  p->d1 = atof( argv[1] ) ;           // write to shared mem
  if ( sem_post( & (p->client) ) )  // awaken server
  {
    perror("Failed to post client's semaphore ") ;
    exit(-1) ;       
  }
  printf("Cliet posted its semaphore\n");
  printf("Cliet now waits for server\n");
  if( sem_wait( & (p->server) ) )  // wait for server
  {
    perror("Failed to wait for server's semaphore ") ;
    exit(-1) ;       
  }

  printf ("\nd1=%8.3f , d2=%8.3f\n" , p->d1, p->d2 );

  // Destroy the shared semaphores. ONLY one process does it
  if( sem_destroy( & (p->client) ) )
  {
    perror("Failed to destroy client's semaphore ") ;
    exit(-1) ;    
  }
  if( sem_destroy( & (p->server) ) )
  {
    perror("Failed to destroy server's semaphore ") ;
    exit(-1) ;    
  }

  // Destroy the shared memory segment
  shmdt( p ) ;
  shmctl( shmid , IPC_RMID , NULL );
  printf ("Client -- Goodbye\n");   
  */
  return 0;
}

