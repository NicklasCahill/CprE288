/**
 * Driver for ping sensor
 * @file ping.c
 * @author
 */

#include "ping_template.h"
#include "Timer.h"

volatile unsigned long START_TIME = 0;
volatile unsigned long END_TIME = 0;
volatile enum{LOW, HIGH, DONE} STATE = LOW; // State of ping echo pulse
uint8_t overflow_count = 0;

void ping_init (void){

    SYSCTL_RCGCGPIO_R |=  0x2;
    SYSCTL_RCGCTIMER_R |= 0x08;

    while((SYSCTL_PRGPIO_R & 0x02) != 0x02){};
    while((SYSCTL_PRTIMER_R & 0x08) != 0x08){};

       GPIO_PORTB_DEN_R |= 0x8;

       GPIO_PORTB_AFSEL_R |= 0x8;

       GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0xFFFF0FFF) | 0x00007000;

       TIMER3_CTL_R &= ~0x100;

       TIMER3_CFG_R = 0x4;

       TIMER3_TBMR_R |= 0x7;
       TIMER3_TBMR_R &= ~0x10;

       TIMER3_CTL_R |= 0xC00;

       TIMER3_TBPR_R |= 0xFF;

       TIMER3_TBILR_R = 0xFFFF;

       TIMER3_IMR_R |= 0x400;
       TIMER3_ICR_R |= 0x400;

       //TIMER3_CTL_R |= 0x100;

       NVIC_EN1_R |= 0x10;

       NVIC_PRI9_R = (NVIC_PRI9_R & 0xFFFFFF0F) | 0x00000020;


    IntRegister(INT_TIMER3B, TIMER3B_Handler);

    IntMasterEnable();

    // Configure and enable the timer


    TIMER3_CTL_R |= 0x0100;

}

void ping_trigger (void){
    STATE = LOW;
    // Disable timer and disable timer interrupt
    TIMER3_CTL_R &= ~0x100;
    TIMER3_IMR_R &= ~0x400;
    // Disable alternate function (disconnect timer from port pin)
    GPIO_PORTB_AFSEL_R &= ~0x8;

    GPIO_PORTB_DIR_R |= 0x08;
    GPIO_PORTB_DATA_R &= ~0x08;
    GPIO_PORTB_DATA_R |= 0x08;
    timer_waitMicros(5);
    GPIO_PORTB_DATA_R &= ~0x08;
    // YOUR CODE HERE FOR PING TRIGGER/START PULSE





    // Clear an interrupt that may have been erroneously triggered
    TIMER3_ICR_R |= 0x400;
    // Re-enable alternate function, timer interrupt, and timer
    GPIO_PORTB_AFSEL_R |= 0x8;
    TIMER3_IMR_R |= 0x400;
    TIMER3_CTL_R |= 0x100;


}

void TIMER3B_Handler(void){


    //printf("interupt");
    if(TIMER3_MIS_R & 0x400) {
        TIMER3_ICR_R |= 0x400;
        if(STATE == LOW) {
            START_TIME = TIMER3_TBR_R;
            STATE = HIGH;
        } else if(STATE == HIGH) {
            END_TIME = TIMER3_TBR_R;
            STATE = DONE;
        }
    }

}

float ping_getDistance (void){

    float distance = 0;
    unsigned long time_diff = 0;
    uint8_t overflow = 0;

    ping_trigger();
    while(STATE != DONE)
    {

    }
    overflow = END_TIME > START_TIME;
    if (overflow) {
        overflow_count += 1;
    }

    time_diff = (START_TIME - END_TIME) + ((unsigned long) overflow<<24);

    distance = (time_diff)/1000 + 3;

    return distance;

}

float getPulsewidth(void)
{
    return START_TIME - END_TIME;
}

float getOverflow(void)
{
    return overflow_count;
}
