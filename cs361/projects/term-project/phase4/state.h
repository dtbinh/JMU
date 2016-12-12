/*
 * state.h
 *
 * Modified on: Oct 26, 2015
 *      Author: Joshua Lyons and Conner Turnbull
 */

#ifndef STATE_H_
#define STATE_H_

typedef struct state state_t;
typedef state_t* event_handler(void);
typedef void action(void);

struct state {
	event_handler*	order_recieved;
	event_handler*	valid_payment;
	event_handler*	invalid_payment;
	event_handler*	manufacturing_failed;
	event_handler*	manufacturing_completed;
	event_handler*	recieved_package;
	event_handler*	lost_package;
	action*		entry_to;
	action*		exit_from;
};

extern state_t*	default_event_handler();
extern void	default_action();

#endif
