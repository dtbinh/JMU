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
	shmflg = IPC_CREAT | S_IRUSR | S_IWUSR;
	
	shmid = shmget(shmkey, SHMEM_SIZE, shmflg);
	if(shmid != -1)
	{
		printf("\nShared memory segment '0x%X' %s %d\n", shmkey,
		"successfully created/Found with id=", shmid);
	}
	else{
		printf("\nFailed to create/find shared memory\"0x%X\". errno=%d\n", shmkey, errno);
		exit(-1);	
	}

	p = (shared_data *) shmat(shmid, NULL, 0);
	if(p == (shared_data *)-1){
		printf("\nFailed to attach shared memory id=%d\n", shmid);
		exit(-1);
	}
	sem_wait(&p->c);
	p->d2 = p->d1 + 1;

	sem_post(&p->s);
	shmdt(p);
	shmctl(shmid, IPC_RMID, NULL);
	printf("Server -- Goodbye\n");
	return 0;
}
