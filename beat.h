/* 
 * File:   beat.h
 * Author: spencerhagedorn
 *
 * Created on April 23, 2019, 3:09 PM
 */
#include <stdbool.h>

#ifndef BEAT_H
#define	BEAT_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* BEAT_H */

static void adcThresholdHandler();
void BEAT_init();
bool BEAT_detected();
void putch(char character);
void BEAT_task();

