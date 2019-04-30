/* 
 * File:   DMX.h
 * Author: spencerhagedorn
 *
 * Created on April 23, 2019, 4:52 PM
 */

#ifndef DMX_H
#define	DMX_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* DMX_H */


void dmx_ISR(void);
void dmx_Enable();
bool dmx_isActive();
void dmx_task();

extern int dmxPointer;
extern uint8_t dmxFrame[514];
extern bool dmxEnable;
extern bool dmxActive;
