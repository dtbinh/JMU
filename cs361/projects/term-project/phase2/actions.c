/*
 * actions.c
 *
 * Modified on: Oct 26, 2015
 *      Author: Joshua Lyons and Conner Turnbull (Group 1)
 */

#ifndef ACTIONS_C_
#define ACTIONS_C_

#include <stdio.h>
#include "actions.h"
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

int attempts = 0;
int order_size = 0;
int parts_remaining = 0;
int total = 0;
sem_t cntMutex;

void getAddress()
{
	printf("Got the address.\n");
}

void chargeClient()
{
	printf("Charged the client.\n");
}

void startWarranty()
{
	printf("Started the warranty.\n");
}

void updateStats(stats value)
{
	if(value == 0)
	{
		printf("Stats updated to: DONE!\n");
	}
	else if(value == 1)
	{
		printf("Stats updated to: LOST!\n");
	}
	else if(value == 2)
	{
		printf("Stats updated to: FAIL!\n");
	}
	else
	{
		printf("ERROR IN UPDATE!!!\n");
	}

}

void refund()
{
	printf("Refunded due to lost package.\n");
}

void resetAttempts()
{
	attempts = 0;
	printf("Attempts have been reset.\n");
}

int incrementAttempts()
{
	attempts += 1;
	printf("Attempts have been incremented.\n");
	if(attempts == 3)
	{
		printf("You have reached the maximum number of attempts.\n");
	}
	else
	{
		int calc;
		calc = (3-attempts);
		printf("The maximum number of payment attempts is 3.  You only have %d attempts left!\n", calc);
	}

	return attempts;
}

void getPaymentMethod()
{
	printf("Payment method has been acquired.\n");
}

void dispatchFactoryLines()
{
	pthread_t tid1, tid2, tid3, tid4, tid5;
	total = 0;

	printf("Factory lines dispatched.\n");

	//sets the random seed value and assigns a random value to order_size between 1000-2000 (inclusively)
	srandom(time(NULL));
	order_size = (random() % 1001) + 1000;
	printf("Order Size: %d\n", order_size);

	parts_remaining = order_size;  //sets parts_remaining, which will be used to keep track of how long the threads will run

	sem_init(&cntMutex, 0, 1);

	//for(int ii = 0; ii < 5; ii++)
	pthread_create(&tid1, NULL, factoryLines, (void *) 1);  //creates the 5 threads
	pthread_create(&tid2, NULL, factoryLines, (void *) 2);
	pthread_create(&tid3, NULL, factoryLines, (void *) 3);
	pthread_create(&tid4, NULL, factoryLines, (void *) 4);
	pthread_create(&tid5, NULL, factoryLines, (void *) 5);

	pthread_join(tid1, NULL); //waiting for each thread to finish
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);
	pthread_join(tid4, NULL);
	pthread_join(tid5, NULL);

	printf("\nTotal Items Produced: %d\n", total);

}
/*
 * Each thread will have its own random capacity and duration
 */
void *factoryLines(void *arg)
{
	int tNum = (int) arg;
	int capacity;
	int duration;
	int numIters = 0;
	int produced = 0;

	capacity = (random() % 41) + 10;  //sets random capacity between 10-50
	duration = (random() % 5) + 1;  //sets random duration between 1-5

	printf("Factory Line %d Capacity: %d\n", tNum, capacity);
	printf("Factory Line %d Duration: %d\n", tNum, duration);

	do
	{
		numIters++;
		sem_wait(&cntMutex);
		if(capacity < parts_remaining)
		{
			produced += capacity;
			parts_remaining -= capacity;
		}
		else
		{
			produced += parts_remaining;
			parts_remaining = 0;
		}
		sem_post(&cntMutex);
		sleep(duration);
	}
	while(parts_remaining > 0);

	printf("Factory Line %d Total Iterations: %d\n", tNum, numIters);
	printf("Factory Line %d Produced %d Items\n", tNum, produced);
	total += produced;
	return NULL;
}

void shutDownFactoryLines()
{
	printf("Factory lines shutdown.\n");
}

#endif

