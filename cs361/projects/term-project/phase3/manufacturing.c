/*
 * manufacturing.c
 *
 * Modified on: Oct 26, 2015
 *      Author: Joshua Lyons and Conner Turnbull (Group 1)
 */

#ifndef MANUFACTURING_C_
#define MANUFACTURING_C_

#include "manufacturing.h"
#include "actions.h"
#include "statemodel.h"

state_t manufacturing = {
	default_event_handler,
    	default_event_handler,
    	default_event_handler,
    	manufacturing_failed,
    	manufacturing_completed,
    	default_event_handler,
    	default_event_handler,
    	entry_to,
    	exit_from
};

state_t* manufacturing_failed()
{
	exit_from();
	updateStats(FAIL);
	return &accepting;
}

state_t* manufacturing_completed()
{
	exit_from();
	chargeClient();
	return &shipping;
}

void entry_to()
{
	dispatchFactoryLines();
}

void exit_from()
{
	shutDownFactoryLines();
}

#endif
