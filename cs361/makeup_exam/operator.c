#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>

#include "operator.h"

int
main ()
{
  int ii;
  int shmid ;
  key_t shmkey;
  int shmflg ;
  shared_data *p;
  pid_t pid;
  char command[50];

  shmkey = SHMEM_KEY ;
  shmflg = IPC_CREAT | S_IRUSR | S_IWUSR  /* | IPC_EXCL */ ;

  shmid = shmget( shmkey , SHMEM_SIZE , shmflg ) ;

  if ( shmid == -1 )
  {
    printf("\nFailed to create/find shared memory '0x%X'.\n", shmkey );
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

  /* Initialize both rendezvous semaphores in the shared memory */   
  if( sem_init( & (p->availSeats) , 1 , 3 )   )
  {
    perror("Failed to init availSeats semaphore ");
    exit(-1) ;     
  }
  if( sem_init( & (p->busFullyLoaded) , 1 , 0 )   )
  {
    perror("Failed to init busFullyLoaded semaphore ") ;
    exit(-1) ;
  }
  if( sem_init( & (p->busMoving) , 1 , 0 )   )
  {
    perror("Failed to init busFullyLoaded semaphore ") ;
    exit(-1) ;
  }

  /* Initialize integers */
  p->onboard = 0;

  /* execlp child processes */
  for (ii = 1; ii <= 5; ii++)
  {
    sprintf(command, "%d", ii);
    pid = fork();
    switch (pid)
    {
      case -1:
        printf("Fork failed\n");
        return 1;

      case 0:
        if ( execlp("./tourist", command, (char*)NULL) == -1 )
        {
          perror("Failed to exec tourist child process");
          exit(-1);
        }

      default:
        break;
    }
  }

  /* create driver */
    pid = fork();
    switch (pid)
    {
      case -1:
        printf("Fork failed\n");
        return 1;

      case 0:
        if ( execlp("./driver", "Driver Bob", (char*)NULL) == -1 )
        {
          perror("Failed to exec driver child process");
          exit(-1);
        }

      default:
        break;
    }

}
