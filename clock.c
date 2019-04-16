#include "mcc_generated_files/tmr0.h"
#include "clock.h"

static time_t currentTime = 0;

static void CLOCK_timerCallback();

void CLOCK_init()
{
    // redirect MCC's timer callback to our custom function
    TMR0_SetInterruptHandler(CLOCK_timerCallback);
    
}

time_t CLOCK_getTime() {
    return currentTime;
}

static void CLOCK_timerCallback() {
    currentTime++;
}

