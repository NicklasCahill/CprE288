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
    ADC_init();
    lcd_init();
    double num , avg;
    int i;
    while(1)
    {
        avg = 0;
        for(i = 0; i < 16; i++)
        {
           avg += returnValue();
        }
        avg = avg / 16;
     num =  97812 * pow(avg , -1.142);
    printf("%f\n%f\n" , num , avg);
    timer_waitMillis(1000);
    }










    
	return 0;
}
