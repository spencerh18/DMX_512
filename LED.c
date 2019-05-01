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
extern bool dmxEnable;

color_t colors[8];

mode_t mode;

void LED_init() {
    mode = MODE_SOUND;
            
    //color: white
    colors[0].white = 255;
    
    // color: red
    colors[1].red = 255;
    
    // color: orange
    colors[2].red = 255;
    colors[2].green = 128;
    
    // color: yellow
    colors[3].red = 255;
    colors[3].green = 255;

    // color: green
    colors[4].green = 255;
    
    // color: cyan
    colors[5].green = 255;
    colors[5].blue = 128;

    // color: blue
    colors[6].blue = 255;

    // color: purple
    colors[7].red = 128;
    colors[7].blue = 255;
    
    // color: black
    colors[8].red = 0;
    colors[8].blue = 0;
    colors[8].green = 0;
    colors[8].white = 0;
}

void LED_setColor(uint8_t R, uint8_t B, uint8_t G, uint8_t W)
{
    CCPR1L = R>>1;
    CCPR2L = B>>1;
    CCPR3L = G>>1;
    CCPR4L = W>>1;
}

void LED_task() {
  if(dmxEnable) {
      mode = MODE_DMX;
  } else {
      mode = MODE_SOUND;
  }
    
  switch (mode)
  {
  case MODE_DMX:
    dmxTask();
    break;

  case MODE_SOUND:
    soundTask();
    break;
  }
}

void dmxTask() {
    //pass each color slot to the setColor function
    LED_setColor(dmxFrame[address], dmxFrame[address + 1], dmxFrame[address + 2], dmxFrame[address + 3]);
}

int i = 0;

void soundTask() {
    
    if (BEAT_detected()) {
        LED_setColor(colors[i].red, colors[i].blue, colors[i].green, colors[i].white);
        i++;
        if(i > 8)
            i = 0;
    }
}
