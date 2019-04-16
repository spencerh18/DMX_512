#include "mcc_generated_files/mcc.h"
#include "PWM.h"
#include "clock.h"
#include "tm1650.h"

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

void Blink1() {
    static bool value = 0;
    static time_t lastTime = 0;
    
    time_t time = CLOCK_getTime();
    if(time <= lastTime + 237)
        return;
    
    lastTime = time;
    value = !value;
    
    if(value)
        TM1650_setDigit(0, '8', 0);
    else
        TM1650_setDigit(0, ' ', 0);
    }

void Blink2() {
    static bool value = 0;
    static time_t lastTime = 0;
    
    time_t time = CLOCK_getTime();
    if(time <= lastTime + 135)
        return;
    
    lastTime = time;
    value = !value;
    
    if(value)
        TM1650_setDigit(1, '8', 0);
    else
        TM1650_setDigit(1, ' ', 0);
    }

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    LED_init();
    CLOCK_init();
    EUSART1_SetRxInterruptHandler(dmx_ISR); //using custom isr above in place of the mcc generated isr
    
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:
    
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    
    TM1650init();

    while (1)
    {
        LED_setColor(dmxFrame[2], dmxFrame[3], dmxFrame[4], dmxFrame[5]); //pass each color slot to the setColor function
        Blink1();
        Blink2();
    }
}
