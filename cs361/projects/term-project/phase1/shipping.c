/*
 * shipping.c
 *
 *  Created on: Oct 08, 2015
 *      Author: Joshua Lyons and Conner Turnbull (Group 1)
 */

#ifndef SHIPPING_C_
#define SHIPPING_C_

#include "shipping.h"
#include "actions.h"
#include "statemodel.h"

state_t shipping = {
	default_event_handler,
    	default_event_handler,
    	default_event_handler,
    	default_event_handler,
    	default_event_handler,
    	recieved_package,
    	lost_package,
    	entry_to,
    	default_action
};

state_t* recieved_package()
{
	updateStats(DONE);
	startWarranty();
	return &accepting;
}

state_t* lost_package()
{
	updateStats(LOST);
	refund();
    return &accepting;
}

void entry_to()
{
    getAddress();
}

#endif
