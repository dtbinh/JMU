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
#include <sys/shm.h>
#include <sys/stat.h>

int attempts = 0;
int order_size = 0;

/*  
*   NAME: getAddress
* 
*   This method gets the address
*/
void getAddress()
{
	printf("Got the address.\n");
}

/*  
*   NAME: chargeClient
* 
*   This method charges the client
*/
void chargeClient()
{
	printf("Charged the client.\n");
}

/*  
*   NAME: startWarranty
* 
*   This method begins the warranty
*/
void startWarranty()
{
	printf("Started the warranty.\n");
}

/*  
*   NAME: updateStats
* 
*   This method takes in a value and prints out the updated stats.
*/
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

/*  
*   NAME: refund
* 
*   This method refunds a lost package
*/
void refund()
{
	printf("Refunded due to lost package.\n");
}

/*  
*   NAME: resetAttempts
* 
*   This method resets attempts
*/
void resetAttempts()
{
	attempts = 0;
	printf("Attempts have been reset.\n");
}

/*  
*   NAME: incrementAttempts
* 
*   This method increments number of attempts
*/
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
		printf("The maximum number of payment attempts is 3. "
					 "You only have %d attempts left!\n", calc);
	}

	return attempts;
}

/*  
*   NAME: getPaymentMethod
* 
*   This method the method of payment
*/
void getPaymentMethod()
{
	printf("Payment method has been acquired.\n");
}

/*  
*   NAME: dispatchFactoryLines
* 
*   This method dispatches the factory manufacturing lines
*/
void dispatchFactoryLines()
{
	int ii;
	pid_t pid;

	printf("Factory lines dispatched.\n");

	/* Create server process */
	pid = fork();
	switch (pid)
	{
		case -1:
			perror("Fork failed");
			exit(-1);

		case 0:
			if ( execlp("gnome-terminal", "superVterm", "-x", "/bin/bash",
				"-c", "./server 66", NULL) == -1 )
			{
				perror("Failed to exec supervisor process");
				exit(-1);
			}

		default:
			break;
	}
}

/*  
*   NAME: shutDownFactoryLines
* 
*   This method shuts down all factory lines
*/
void shutDownFactoryLines()
{
	printf("Factory lines shutdown.\n");
}

#endif
