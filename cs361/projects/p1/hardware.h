/*
 * hardware.h
 *
 *  Created on: Sep 14, 2015
 *      Author: Joshua Lyons
 */

#ifndef hardware_h
#define hardware_h

typedef enum
{
    LED_OFF,
    LED_ON,
    LED_NUMBER_OF_SETTINGS
} led_setting;

typedef enum
{
    MOTOR_CLOSING,
    MOTOR_OFF,
    MOTOR_OPENING,
    MOTOR_NUMBER_OF_SETTINGS
} motor_setting;

typedef enum
{
    CLOSE_BUTTON_PRESSED,
    CLOSED_DETECTED,
    OPEN_BUTTON_PRESSED,
    OPENED_DETECTED,
    NUMBER_OF_EVENTS
} event;

void set_closed_indicator(led_setting value);
void set_opened_indicator(led_setting value);
void set_motor(motor_setting value);

#endif
