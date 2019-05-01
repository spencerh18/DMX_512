/* 
 * File:   clock.h
 * Author: spencerhagedorn
 *
 * Created on April 16, 2019, 3:11 PM
 */

#ifndef CLOCK_H
#define	CLOCK_H

typedef uint16_t time_t;

void CLOCK_init();
time_t CLOCK_getTime();

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* CLOCK_H */

