#include <semaphore.h>

typedef struct
{
  sem_t availSeats, busFullyLoaded, busMoving;
  int onboard;
} shared_data;

#define SHMEM_KEY  0x456
#define SHMEM_SIZE sizeof(shared_data)
