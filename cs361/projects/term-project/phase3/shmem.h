#include <semaphore.h>

typedef struct {
	sem_t factory_lines_finished, print_aggregates, cntMutex;
	int /*lines_active,*/ parts_remaining, num_iters, total;
} shared_data;

#define SHMEM_KEY  0x100
#define SHMEM_SIZE sizeof(shared_data)
