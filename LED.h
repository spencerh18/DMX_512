/* 
 * File:   LED.h
 * Author: spencerhagedorn
 *
 * Created on April 23, 2019, 3:39 PM
 */

#ifndef LED_H
#define	LED_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* LED_H */

#include <stdint.h>

void LED_task();
void soundTask();
void dmxTask();
//void autoTask();
void LED_setColor(uint8_t R, uint8_t B, uint8_t G, uint8_t W);
void LED_init();

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t white;
} color_t;

typedef enum {
    MODE_AUTO,
    MODE_DMX,
    MODE_SOUND
} mode_t;
