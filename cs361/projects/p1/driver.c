/*
 * driver.c
 *
 *  Created on: Sep 14, 2015
 *      Author: Joshua Lyons and Conner Turnbull (Group 1)
 */

#include <stdio.h>
#include "statemodel.h"

int main()
{
    printf("Current State is: OPENED\n");
    int c;
    event e;
    int exit = 0; // if 1, exit loop

    while (!exit)
    {
        c = getchar();

        switch (c)
        {
            case 'c':  //close button pressed
                e = CLOSE_BUTTON_PRESSED;
                handle_event (e);
                break;
            case 'C': //closed detected
                e = CLOSED_DETECTED;
                handle_event (e);
                break;
            case 'o': //open button pressed
                e = OPEN_BUTTON_PRESSED;
                handle_event (e);
                break;
            case 'O': //opened deteced
                e = OPENED_DETECTED;
                handle_event (e);
                break;
            case 'x': // exit
                exit = 1;
                break;
        }
    }

    return 0;
}
