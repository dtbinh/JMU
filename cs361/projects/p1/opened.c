/*
 * opened.c
 *
 *  Created on: Sep 14, 2015
 *      Author: Joshua Lyons and Conner Turnbull (Group 1)
 */

#ifndef OPENED_C_
#define OPENED_C_

#include "opened.h"
#include "hardware.h"
#include "statemodel.h"

state_t opened = {
		close_button_pressed,
		default_event_handler,
		default_event_handler,
		default_event_handler,
		entry_to,
		exit_from
};

state_t* close_button_pressed()
{
	exit_from();
	return &closing;
}

void entry_to()
{
	set_opened_indicator(LED_ON);
}

void exit_from()
{
	set_opened_indicator(LED_OFF);
}

#endif
