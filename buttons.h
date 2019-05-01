/* 
 * File:   buttons.h
 * Author: spencerhagedorn
 *
 * Created on April 16, 2019, 4:38 PM
 */

#ifndef BUTTONS_H
#define	BUTTONS_H

#include <stdint.h>
#include <stdbool.h>
    
typedef enum {
    EVENT_IDLE,
    EVENT_PRESSED,
    EVENT_HELD
} event_t;

typedef enum {
    STATE_UNPRESSED,
    STATE_PRESSED
} btnState_t;

typedef struct {
    volatile uint8_t* port;
    uint8_t pin;
    btnState_t state;
    btnState_t lastState;
    event_t event;
} button_t;

static void init(button_t* btn, volatile uint8_t* port, uint8_t pin);
void BUTTONS_init();
extern button_t *up, *down, *enter, *menu;
void BUTTONS_task();
bool BUTTONS_isClicked(button_t* button);
bool BUTTONS_isHeld(button_t* button);

#ifdef	__cplusplus
extern "C" {
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* BUTTONS_H */

