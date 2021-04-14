/**
 * @file lab8_template.c
 * @author
 * Template file for CprE 288 Lab 8
 */

#include "Timer.h"
#include "lcd.h"
#include "ping_template.h"

// Uncomment or add any include directives that are needed

#warning "Possible unimplemented functions"
#define REPLACEME 0

int main(void) {
   //resetSimulationBoard();
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	ping_init();

	// YOUR CODE HERE
	while(1)
	{
	    timer_waitMillis(1000);
	    float distance = 0;
	    distance = ping_getDistance();
	    printf( "%.2f \n", distance);
	    lcd_printf("Pulse Width: %.2f" , getPulsewidth());
	    timer_waitMillis(1500);
	    lcd_printf("Overflow: %.2f" , getOverflow());

	}
      // YOUR CODE HERE




}
