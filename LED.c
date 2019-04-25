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

extern time_t dmxTime;
extern uint8_t dmxFrame[514];
extern bool dmxEnable = false;

void LED_init() {
    color_t colors[8];
    
    // color 0: red
    colors[0].red = 255;

    // color 1: green
    colors[1].green = 255;

    // color 2: blue
    colors[2].blue = 255;
    
    // color 3: white
    colors[3].white = 255;

    // color 4: orange
    colors[4].red = 255;
    colors[4].green = 128;

    // color 5: purple
    colors[5].red = 128;
    colors[5].blue = 255;

    // colors 6: yellow
    colors[6].red = 255;
    colors[6].green = 255;

    // colors 7: seafoam
    colors[7].green = 255;
    colors[7].blue = 128;

    // colors 8: everything
    colors[8].red = 255;
    colors[8].green = 255;
    colors[8].blue = 255;
    colors[8].white = 255;
}

void LED_setColor(uint8_t R, uint8_t B, uint8_t G, uint8_t W)
{
    CCPR1L = R>>1;
    CCPR2L = B>>1;
    CCPR3L = G>>1;
    CCPR4L = W>>1;
}

void LED_task() {
  switch (MODE_SOUND)
  {
  case MODE_AUTO:
    autoTask();
    break;

  case MODE_DMX:
    dmxTask();
    break;

  case MODE_SOUND:
    soundTask();
    break;
  }
}

void autoTask() {
    if(dmxEnable == true) {
        soundTask;
    } else {
        dmxTask;
    }
}

void dmxTask() {
    //pass each color slot to the setColor function
    LED_setColor(dmxFrame[address], dmxFrame[address + 1], dmxFrame[address + 2], dmxFrame[address + 3]);
}

time_t lastRun = 0;

void soundTask() {
    if (CLOCK_getTime() - lastRun < 100)
        return;

    lastRun = CLOCK_getTime();
    LATC5 = 0;
    
    if (BEAT_detected()) {
        LATC5 = 1;
    }
}
