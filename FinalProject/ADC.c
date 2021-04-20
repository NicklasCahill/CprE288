/*
*
*   uart.c
*
*
*
*   @author
*   @date
*/

#include <ADC.h>
#include <inc/tm4c123gh6pm.h>
#include <stdint.h>

void ADC_init(void){

    SYSCTL_RCGCADC_R |= 0x01;
    SYSCTL_RCGCGPIO_R |=  0b000010;

    while((SYSCTL_PRGPIO_R & 0x02) != 0x02){};


    GPIO_PORTB_DIR_R &= ~0x10;

    GPIO_PORTB_AFSEL_R |= 0x10;

    GPIO_PORTB_DEN_R &= ~0x10;

    GPIO_PORTB_AMSEL_R |= 0x10;

    ADC0_PC_R &= ~0xF;
    ADC0_PC_R |= 0x1;             // 8) configure for 125K samples/sec
    ADC0_SSPRI_R = 0x0123;        // 9) Sequencer 3 is highest priority

    ADC0_ACTSS_R &= ~0x0008;

    ADC0_EMUX_R |= 0xD3;

    ADC0_PSSI_R |= 0x8;

    ADC0_SSMUX3_R &= ~0x000F;

    ADC0_SSMUX3_R |= 0xA;

    ADC0_SSCTL3_R |= 0x0006;

    ADC0_IM_R &= ~0x0008;

    ADC0_ACTSS_R |= 0x0008;






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



