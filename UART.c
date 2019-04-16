#pragma config WDTE = OFF
#include <xc.h>
#include <stdint.h>
#include "UART.h"

void UART_init() {
    TRISB = 0; // set as output
    RB7PPS = 0x0F; // route TX1 output to RxyPPS output
    // set the baud to 9600
    TX1STAbits.BRGH = 1; 
    BAUD1CONbits.BRG16 = 0;
    SP1BRG = 25;
    
    TX1STAbits.TXEN = 1; // enable the transmitter
    RC1STAbits.SPEN = 1; // enable the EUSART
}
