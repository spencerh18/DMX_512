#include "controller.h"
#include "buttons.h"
#include "clock.h"
#include "tm1650.h"

uint16_t address = 1;

void CONTROLLER_init() {
    TM1650_fastPrintNum(address);
}

/**
 * Increments the address and updates the display
 */
void address_inc()
{
    if(address == 512)
        address = 1;
    else
        address++;
    
    // update the display
    TM1650_fastPrintNum(address);
}

/**
 * Decrements the address and updates the display
 */
void address_dec() 
{
    if(address == 1)
        address = 512;
    else
        address--;  
    
    // update the display
    TM1650_fastPrintNum(address);
}

void CONTROLLER_task() {
    if (BUTTONS_isClicked(up)) {
        address_inc();
        
    } else if (BUTTONS_isClicked(down)) {
        address_dec();
    }
    if (BUTTONS_isHeld(up)) {
        address_inc();
        
    } else if (BUTTONS_isHeld(down)) {
        address_dec();
    }
}
