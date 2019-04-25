/* 
 * File:   controller.h
 * Author: spencerhagedorn
 *
 * Created on April 16, 2019, 4:38 PM
 */


#ifndef CONTROLLER_H
#define	CONTROLLER_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* CONTROLLER_H */

#include <stdint.h>

typedef enum {
    MENU_DMX,
    MENU_AUTOSPEED
} menu_t;

void CONTROLLER_init();
void address_inc();
void address_dec();
void CONTROLLER_task();
static void dmxAddressViewInit();
static void setMenu(menu_t newMenu);

extern uint16_t address;
