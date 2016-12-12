/*
 * statemodel.h
 *
 *  Created on: Oct 08, 2015
 *      Author: Joshua Lyons and Conner Turnbull
 */

#ifndef statemodel_h
#define statemodel_h
#include <stdlib.h>
#include "actions.h"
#include "state.h"

extern state_t accepting;
extern state_t processing;
extern state_t manufacturing;
extern state_t shipping;

void handle_event(event current_event);

#endif

