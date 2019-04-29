#include "mcc_generated_files/mcc.h"
#include "PWM.h"
#include "clock.h"
#include "tm1650.h"
#include "controller.h"
#include "buttons.h"
#include "beat.h"
#include "DMX.h"
#include "LED.h"
#include <stdbool.h>
#include <stdint.h>

int dmxPointer = 0;
uint8_t dmxFrame[514]; //size of 514 because the first two are the break and the start and then 512 bytes

void dmx_ISR(void) {
    if(RC1STAbits.OERR){ //check for overrun error (allows for debugging)
        RC1STAbits.CREN = 0;
        RC1STAbits.CREN = 1;
    }
    if(RC1STAbits.FERR){ //check for framing error (allows you to differentiate between frames, end of address/slots)
        dmxPointer = 0;
    }
    
    dmxFrame[dmxPointer++] = RC1REG; //reads data from slots and stores it in the array
}

bool dmxEnable = false;

void dmx_Enable() {
    if(dmxPointer > 0) {
        dmxEnable = true;
    }
}

bool dmx_isActive() {
    return false;
}
