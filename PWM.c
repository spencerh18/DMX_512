#pragma config WDTE = OFF
#include <xc.h>
#include <stdint.h>
#include "PWM.h"

#define _XTAL_FREQ 4000000

void LED_init()
{
    TRISC = 0b00000111; //LED output
    
    RC7PPS = 0x09; //RED
    RC3PPS = 0x0A; //BLUE
    RC6PPS = 0x0B; //GREEN
    RC4PPS = 0x0C; //WHITE
    
    T2CLKCON = 0x01; // configure Timer2's clock source to Fosc/4
    T2CONbits.ON = 1; // turn on Timer2
    
    CCP1CONbits.CCP1EN = 1;
    CCP1CONbits.MODE = 0b1100;
    CCP2CONbits.CCP2EN = 1;
    CCP2CONbits.MODE = 0b1100;
    CCP3CONbits.CCP3EN = 1;
    CCP3CONbits.MODE = 0b1100;
    CCP4CONbits.CCP4EN = 1;
    CCP4CONbits.MODE = 0b1100;
    
}

void LED_setColor(uint8_t R, uint8_t B, uint8_t G, uint8_t W)
{
    CCPR1L = R>>1;
    CCPR2L = B>>1;
    CCPR3L = G>>1;
    CCPR4L = W>>1;
}