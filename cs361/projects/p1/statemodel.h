/*
 * statemodel.h
 *
 *  Created on: Sep 14, 2015
 *      Author: joshualyons
 */

#ifndef statemodel_h
#define statemodel_h
#include <stdlib.h>
#include "hardware.h"
#include "state.h"

extern state_t closed;
extern state_t closing;
extern state_t opened;
extern state_t opening;

void handle_event(event current_event);

#endif
