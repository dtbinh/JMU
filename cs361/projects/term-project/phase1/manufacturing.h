/*
 * manufacturing.h
 *
 *  Created on: Oct 08, 2015
 *      Author: Joshua Lyons and Conner Turnbull
 */

#ifndef MANUFACTURING_H_
#define MANUFACTURING_H_

#include "state.h"


static state_t*	manufacturing_failed();
static state_t*	manufacturing_completed();
static void		entry_to();
static void		exit_from();

#endif

