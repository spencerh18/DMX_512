#include "mcc_generated_files/mcc.h"
#include "PWM.h"
#include "clock.h"
#include "tm1650.h"
#include "controller.h"
#include "buttons.h"
#include "beat.h"
#include "DMX.h"
#include "LED.h"

#define _XTAL_FREQ 4000000

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
    
    //prevent the I2C bus from hanging at the start
    __delay_ms(500);
    
    TM1650init();
    CONTROLLER_init();
    BUTTONS_init();
    BEAT_init();
    LED_init();
    
    
    while (1)
    {
        BUTTONS_task();
        CONTROLLER_task();
        LED_task();
        BEAT_task();
    }
}
