/*
 * shipping.h
 *
 * Modified on: Oct 26, 2015
 *      Author: Joshua Lyons and Conner Turnbull
 */

#ifndef SHIPPING_H_
#define SHIPPING_H_

#include "state.h"

static state_t* recieved_package();
static state_t* lost_package();
static void entry_to();

#endif
