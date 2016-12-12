/*
 * opening.c
 *
 *  Created on: Sep 14, 2015
 *      Author: Joshua Lyons and Conner Turnbull (Group 1)
 */

#ifndef OPENING_C_
#define OPENING_C_

#include "opening.h"
#include "hardware.h"
#include "statemodel.h"

state_t opening = {
		close_button_pressed,
		default_event_handler,
		default_event_handler,
		opened_detected,
		entry_to,
		default_action
};

state_t* close_button_pressed()
{
    return &closing;
}

state_t* opened_detected()
{
    set_motor(MOTOR_OFF);
    return &opened;
}

void entry_to()
{
    set_motor(MOTOR_OPENING);
}

#endif
