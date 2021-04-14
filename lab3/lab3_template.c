/**
 * lab3_template.c
 * 
 * Template file for CprE 288 lab 3
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 */

#include "button.h"
#include "Timer.h"
#include "lcd.h"
#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART)
                         // PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity,  COM1

//#warning "Possible unimplemented functions"
#define REPLACEME 0



int main(void) {
	button_init();
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	            // Don't forget to initialize the cyBot UART before trying to use it
	cyBot_uart_init();
	// YOUR CODE HERE
	int n = 0;

	while(1)
	{
	    n = button_getButton();


	        lcd_printf("%d" , n);


      // YOUR CODE HERE
  


	
	}
	
}
