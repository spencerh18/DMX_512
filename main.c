#include "mcc_generated_files/mcc.h"
#include "PWM.h"
#include "clock.h"
#include "tm1650.h"
#include "controller.h"
#include "buttons.h"

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


void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    CLOCK_init();
    EUSART1_SetRxInterruptHandler(dmx_ISR); //using custom isr above in place of the mcc generated isr
    
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:
    
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    
    TM1650init();
    CONTROLLER_init();
    BUTTONS_init();
    
    while (1)
    {
        BUTTONS_task();
        CONTROLLER_task();
        //pass each color slot to the setColor function
        LED_setColor(dmxFrame[address], dmxFrame[address + 1], dmxFrame[address + 2], dmxFrame[address + 3]);
    }
}
