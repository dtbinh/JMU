/*
 * state.h
 *
 *  Created on: Sep 14, 2015
 *      Author: Joshua Lyons
 */

#ifndef STATE_H_
#define STATE_H_

typedef struct state state_t;
typedef state_t* event_handler(void);
typedef void action(void);

struct state {
	event_handler*	close_button_pressed;
	event_handler*	closed_detected;
	event_handler*	open_button_pressed;
	event_handler*	opened_detected;
	action*			entry_to;
	action*			exit_from;
};

extern state_t*	default_event_handler();
extern void		default_action();

#endif
