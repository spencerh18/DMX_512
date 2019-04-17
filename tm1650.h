// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */


// declare functions from tm1650.c file
static void writeData(uint8_t address, uint8_t data);
void TM1650init();
void TM1650_setDigit(uint8_t digit, uint8_t data, uint8_t DP);
void putch(char holder);
void TM1650_fastPrintNum(uint16_t num);
