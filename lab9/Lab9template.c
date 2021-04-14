/// Simple 'Hello, world' program
/**
 * This program prints "Hello, world" to the LCD screen
 * @author Chad Nelson
 * @date 06/26/2012
 *
 * updated: phjones 9/3/2019
 * Description: Added timer_init call, and including Timer.h
 */

#include "Timer.h"
#include "lcd.h"
#include <math.h>

int main (void) {
   //resetSimulationBoard();
    timer_init();
    lcd_init();
    Servo_init();

    move_servo(-25);
    
	return 0;
}


