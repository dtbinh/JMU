/*
 * CS-450 Fall 2015 Demo of IPC using 
 * Written By:
 *  1- Dr. Mohamed Aboutabl
 *  Submitted on:
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/shm.h>
#include <sys/stat.h>

#include "shmem-ex.h"

int main(int argc, char *argv[])
{
  int shmid;
  key_t shmkey;
  int shmflg;
  shared_data *p;

  shmkey = SHMEM_KEY;
  shmflg = IPC_CREAT | S_IRUSR | S_IWUSR; /* | IPC_EXCL */

    shmid = shmget(shmkey, SHMEM_SIZE, shmflg);
  if (shmid != -1) {
      printf("\nShared memory segment '0x%X' %s %d\n", shmkey, "successfully created/found with id", shmid);
  }
  else {
      printf("\nFailed to create/find shared memory '0x%X'.\n", shmkey);
      perror("Reason: ");
      exit(-1);
  }
  p = (shared_data *) shmat(shmid, NULL, 0);
  if (p == (shared_data *) -1) {
      printf("\nFailed to attach shared memory id=%d\n", shmid);
      exit(-1);
  }

  p->d1 = 15.0;
  sem_init(&p->c, 1, 0); 
  sem_init(&p->s, 1, 0); 
  /* now wait for server process to do its part */
  sem_post(&p->c);
  sem_wait(&p->s);

  printf("\nd1=%8.3f, d2=%8.3f\n", p->d1, p->d2);

  shmdt(p);
  shmctl(shmid, IPC_RMID, NULL);
  printf("Client -- Goodbye\n");
  return 0;
}
