/*
*
*   uart.h
*
*   Used to set up the RS232 connector and WIFI module
*   Functions for communicating between CyBot and PC via UART1
*   Serial parameters: Baud = 115200, 8 data bits, 1 stop bit,
*   no parity, no flow control on COM1, FIFOs disabled on UART1
*
*   @author Dane Larson
*   @date 07/18/2016
*   Phillip Jones updated 9/2019, removed WiFi.h, Timer.h
*   Diane Rover updated 2/2020, changed receive return type to char
*/

#ifndef SERVO_H_
#define SERVO_H_

#include <inc/tm4c123gh6pm.h>

// UART1 device initialization for CyBot to PuTTY
void Servo_init(void);

int returnValue(void);

void move_servo(int degrees);

#endif /* SERVO_H_ */
