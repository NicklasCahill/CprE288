/**
 * lab5_template.c
 *
 * Template file for CprE 288 Lab 5
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 *
 * @author Phillip Jones, updated 6/4/2019
 * @author Diane Rover, updated 2/25/2021
 */

#include "button.h"
#include "timer.h"
#include "lcd.h"

#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART1)
                         // PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity, COM1

#include "cyBot_FindObjects.h"  // Scan the CyBot sensors to find objects


#warning "Possible unimplemented functions"
#define REPLACEME 0



int main(void) {
    resetSimulationBoard();
	//button_init();
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();

  // initialize the cyBot UART1 before trying to use it

  // (Uncomment ME for UART init part of lab)
	 cyBot_uart_init_clean();  // Clean UART initialization, before running your UART GPIO init code
	 uart_init();
	 //uart_init();
	// Complete this code for configuring the GPIO PORTB part of UART1 initialization (your UART GPIO init code)
/*
      SYSCTL_RCGCGPIO_R |= 0b000010;
	    while ((SYSCTL_PRGPIO_R & 0x10) == 0) {};
	  GPIO_PORTB_DEN_R |= 0x03;
	  GPIO_PORTB_AFSEL_R |= 0x03;
      GPIO_PORTB_PCTL_R &= ~0x000000FF;     // Force 0's in the desired locations
      GPIO_PORTB_PCTL_R |= 0x00000011;     // Force 1's in the desired locations
		 // Or see the notes for a coding alternative to assign a value to the PCTL field

    // (Uncomment ME for UART init part of lab)*/
		 //cyBot_uart_init_last_half();  // Complete the UART device configuration
	 int i = 0;
	 char password[20] = "";
	 char letter;
	// YOUR CODE HERE

	// uart_sendStr(password);



	while(1)
	{

	 for(i = 0; sizeof(password); i++)
	 {
	     if(i >= 20)
	     {
	         uart_sendChar('\n');
	         password[i] = '\0';
	         break;
	     }
	     password[i] = uart_receive();
	     uart_sendChar(password[i]);

	     if(password[i] == '\r')
	     {
	         uart_sendChar('\n');
	         password[i] = '\0';
	         break;

	     }

	 }
	 lcd_puts(password);
	}
	     /*for(i = 0; i < sizeof(password); i++)
	     {
	     uart_sendChar(password[i]);
	     }*/
	    //cyBot_sendByte('a');
      // YOUR CODE HERE


	//}

}
