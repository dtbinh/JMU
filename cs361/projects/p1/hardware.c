/*
 * hardware.c
 *
 *  Created on: Sep 14, 2015
 *      Author: Joshua Lyons and Conner Turnbull (Group 1)
 */

#include <stdio.h>
#include "hardware.h"


void 
set_closed_indicator(led_setting value)
{
    switch (value)
    {
        case LED_OFF:
            printf("The closed LED is now off.\n");
            break;
        case LED_ON:
            printf("The closed LED is now on.\n");
            break;
    }
}

void 
set_opened_indicator(led_setting value)
{
    switch (value)
    {
        case LED_OFF:
            printf("The opened LED is now off.\n");
            break;
        case LED_ON:
            printf("The opened LED is now on.\n");
            break;
    }
}

void
set_motor(motor_setting value)
{
    switch (value)
    {
        case MOTOR_CLOSING:
            printf("The motor is now closing the door.\n");
            break;
        case MOTOR_OFF:
            printf("The motor is now off.\n");
            break;
        case MOTOR_OPENING:
            printf("The motor is now opening the door.\n");
            break;
    }
}
