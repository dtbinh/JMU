/*
 * CS-450 Fall 2015
 * Demo of IPC using Shared Memory
 * Written By:
 *  1- Dr. Mohamed Aboutabl
 *  Submitted on:
 */
#include <semaphore.h>
#include <pthread.h>

typedef struct {
    sem_t c;
    sem_t s;
    double d1;
    double d2;
} shared_data;

#define SHMEM_KEY 0x100
#define SHMEM_SIZE sizeof(shared_data)
