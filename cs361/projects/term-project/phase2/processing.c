/*
 * processing.c
 *
 * Modified on: Oct 26, 2015
 *      Author: Joshua Lyons and Conner Turnbull (Group 1)
 */

#ifndef PROCESSING_C_
#define PROCESSING_C_

#include "processing.h"
#include "actions.h"
#include "statemodel.h"

state_t processing = {
	default_event_handler,
	valid_payment,
    	invalid_payment,
    	default_event_handler,
    	default_event_handler,
    	default_event_handler,
    	default_event_handler,
    	entry_to,
    	default_action
};

state_t* valid_payment()
{
    return &manufacturing;
}

state_t* invalid_payment()
{
	int attempts;

	attempts = incrementAttempts();
	if(attempts < 3)
	{
		return &processing;
	}
	else
	{
		return &accepting;
	}
}

void entry_to()
{
    getPaymentMethod();
}

#endif
