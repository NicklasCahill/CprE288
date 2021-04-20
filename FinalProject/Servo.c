/*
*
*   uart.c
*
*
*
*   @author
*   @date
*/

#include <inc/tm4c123gh6pm.h>
#include <stdint.h>
#include <Servo.h>

void Servo_init(void){

   SYSCTL_RCGCGPIO_R |= 0x02;
   SYSCTL_RCGCTIMER_R |= 0x02;

   while((SYSCTL_PRTIMER_R & 0x02) != 0x02){};
   while((SYSCTL_PRGPIO_R & 0x02) != 0x02){};

   GPIO_PORTB_DIR_R |= 0x20;
   GPIO_PORTB_DEN_R |= 0x20;
   GPIO_PORTB_AFSEL_R |= 0x20;
   GPIO_PORTB_PCTL_R |= 0x00700000;

   TIMER1_CTL_R &= 0xFEFF;
   TIMER1_CFG_R |= 0x4;
   TIMER1_TBMR_R |= 0xA;

   int pulse_period = 320000;

   TIMER1_TBILR_R = pulse_period & 0xFFFF;
   TIMER1_TBPR_R = pulse_period >> 16;
   TIMER1_CTL_R |= 0x0100;



}

int returnValue(void)
{
    int result;
    ADC0_PSSI_R = 0x0008;
    while((ADC0_RIS_R & 0x08) == 0){};
    result = ADC0_SSFIFO3_R & 0x00000FFF;
    ADC0_ISC_R = 0x0008;
    return result;

}

void move_servo(int degrees)
{
    unsigned int turn = degrees*(133) + 10000;

    TIMER1_TBMATCHR_R = (320000 - turn) & 0xFFFF;
    TIMER1_TBPMR_R = (320000 - turn) >> 16;


}

