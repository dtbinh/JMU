/*
 * actions.h
 *
 * Modified on: Oct 26, 2015
 *      Author: Joshua Lyons and Conner Turnbull
 */

#ifndef ACTIONS_H_
#define ACTIONS_H_

typedef enum
{
    DONE,
    LOST,
    FAIL
} stats;

typedef enum
{
	ORDER_RCVD,
	VALID_PYMNT,
	INVALID_PYMNT,
	MANUF_FAILED,
	MANUF_COMPLETED,
	RECIEVED,
	LOST_PACKAGE
} event;

void getAddress();
void chargeClient();
void startWarranty();
void updateStats(stats value);
void refund();
void resetAttempts();
int incrementAttempts();
void getPaymentMethod();
void dispatchFactoryLines();
void shutDownFactoryLines();
void *factoryLines(void *arg);

#endif
