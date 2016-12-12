/*
 * driver.c
 *
 *  Created on: Oct 08, 2015
 *      Author: Joshua Lyons and Conner Turnbull (Group 1)
 */

#include <stdio.h>
#include "statemodel.h"

int main()
{
    printf("Current State is: ACCEPTING\n");
    int c;
    event e;
    int exit = 0; // if 1, exit loop

    while (!exit)
    {
        c = getchar();

        switch (c)
        {
            case 'O':  //order recieved
                e = ORDER_RCVD;
                handle_event (e);
                break;
            case 'V': //valid payment
                e = VALID_PYMNT;
                handle_event (e);
                break;
            case 'I': //invalid payment
                e = INVALID_PYMNT;
                handle_event (e);
                break;
            case 'F': //manufactering faild
                e = MANUF_FAILED;
                handle_event (e);
                break;
            case 'C': //manufactering complete
                e = MANUF_COMPLETED;
                handle_event (e);
                break;
            case 'R': //delivery recieved
                e = RECIEVED;
                handle_event (e);
                break;
            case 'L': //delivery lost
                e = LOST_PACKAGE;
                handle_event (e);
                break;
            case 'X': // exit
                exit = 1;
                break;
        }
    }

    return 0;
}
