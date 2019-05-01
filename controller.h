/* 
 * File:   controller.h
 * Author: spencerhagedorn
 *
 * Created on April 16, 2019, 4:38 PM
 */


#ifndef CONTROLLER_H
#define	CONTROLLER_H

#include <stdint.h>

void CONTROLLER_init();
void address_inc();
void address_dec();
void CONTROLLER_task();

extern uint16_t address;

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* CONTROLLER_H */

