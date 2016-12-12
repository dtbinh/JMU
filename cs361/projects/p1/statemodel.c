/*
 * statemodel.c

 *
 *  Created on: Sep 14, 2015
 *      Author: Joshua Lyons and Conner Turnbull (Group 1)
 */

#ifndef statemodel_c
#define statemodel_c
#include "statemodel.h"
#include <stdlib.h>
#include <stdio.h>

static state_t * current_state = &opened;

void handle_event( event current_event )
{
    state_t * next_state;

    next_state = NULL;
        switch( current_event )
        {
            case CLOSE_BUTTON_PRESSED:
                next_state = current_state -> close_button_pressed();
                break;
            case CLOSED_DETECTED:
                next_state = current_state -> closed_detected();
                break;
            case OPEN_BUTTON_PRESSED:
                next_state = current_state -> open_button_pressed();
                break;
            case OPENED_DETECTED:
                next_state = current_state -> opened_detected();
                break;
        }

        if (next_state != NULL)
        {
            current_state = next_state;

            current_state -> entry_to();

            if (current_state == &closing)
            {
                printf("Current State is: CLOSING\n");
            }
            else if (current_state == &closed)
            {
                printf("Current State is: CLOSED\n");
            }
            else if (current_state == &opening)
            {
                printf("Current State is: OPENING\n");
            }
            else if (current_state == &opened)
            {
                printf("Current State is: OPENED\n");
            }
        }

}

#endif
