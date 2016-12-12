/*
 * accepting.c
 *
 * Modified on: Oct 26, 2015
 *      Author: Joshua Lyons and Conner Turnbull (Group 1)
 */

#ifndef ACCEPTING_C
#define ACCEPTING_C

#include "accepting.h"
#include "actions.h"
#include "statemodel.h"

state_t accepting = {
	order_recieved,
    	default_event_handler,
    	default_event_handler,
    	default_event_handler,
    	default_event_handler,
    	default_event_handler,
    	default_event_handler,
    	default_action,
    	default_action
};

/*  
*   NAME: order_recieved
* 
*   This method handles recieved orders
*/
state_t* order_recieved()
{
    resetAttempts();
    return &processing;
}

#endif

