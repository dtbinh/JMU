/*
 * statemodel.c
 *
 * Modified on: Oct 26, 2015
 *      Author: Joshua Lyons and Conner Turnbull (Group 1)
 */

#ifndef statemodel_c
#define statemodel_c
#include "statemodel.h"
#include <stdlib.h>
#include <stdio.h>

static state_t * current_state = &accepting;

void handle_event( event current_event )
{
    state_t * next_state;

    next_state = NULL;
        switch( current_event )
        {
            case ORDER_RCVD:
                next_state = current_state -> order_recieved();
                break;
            case VALID_PYMNT:
                next_state = current_state -> valid_payment();
                break;
            case INVALID_PYMNT:
                next_state = current_state -> invalid_payment();
                break;
            case MANUF_FAILED:
                next_state = current_state -> manufacturing_failed();
                break;
            case MANUF_COMPLETED:
                next_state = current_state -> manufacturing_completed();
                break;
            case RECIEVED:
                next_state = current_state -> recieved_package();
                break;
            case LOST_PACKAGE:
                next_state = current_state -> lost_package();
                break;
        }

        if (next_state != NULL)
        {
            current_state = next_state;

            current_state -> entry_to();

            if (current_state == &accepting)
            {
                printf("Current State is: ACCEPTING\n");
            }
            else if (current_state == &processing)
            {
                printf("Current State is: PROCESSING\n");
            }
            else if (current_state == &manufacturing)
            {
                printf("Current State is: MANUFACTURING\n");
            }
            else if (current_state == &shipping)
            {
                printf("Current State is: SHIPPING\n");
            }
        }
}

#endif
