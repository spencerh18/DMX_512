
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "mcc_generated_files/i2c1.h"
#include "tm1650.h"

#define _XTAL_FREQ 4000000

static int tab = 0;

const uint8_t charTable[] = 
{
    0x00, 0x82, 0x21, 0x00, 0x00, 0x00, 0x00, 0x02, 0x39, 0x0F, 0x00, 0x00, 0x00, 0x40, 0x80, 0x00,
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7f, 0x6f, 0x00, 0x00, 0x00, 0x48, 0x00, 0x53,
    0x00, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x6F, 0x76, 0x06, 0x1E, 0x00, 0x38, 0x00, 0x54, 0x3F,
    0x73, 0x67, 0x50, 0x6D, 0x78, 0x3E, 0x00, 0x00, 0x00, 0x6E, 0x00, 0x39, 0x00, 0x0F, 0x00, 0x08, 
    0x63, 0x5F, 0x7C, 0x58, 0x5E, 0x7B, 0x71, 0x6F, 0x74, 0x02, 0x1E, 0x00, 0x06, 0x00, 0x54, 0x5C,
    0x73, 0x67, 0x50, 0x6D, 0x78, 0x1C, 0x00, 0x00, 0x00, 0x6E, 0x00, 0x39, 0x30, 0x0F, 0x00, 0x00 
};

static void writeData(uint8_t address, uint8_t data)
{
    I2C1_MESSAGE_STATUS status = I2C1_MESSAGE_PENDING;
    I2C1_MasterWrite(&data, 1, address, &status);
    while( status == I2C1_MESSAGE_PENDING ); // wait for transaction to complete
}

void TM1650_setDigit(uint8_t digit, uint8_t data, uint8_t DP)
{
    uint8_t value; 
    value = (charTable[data-32]); // get charTable[] value
    if(DP == 1) // if DP, add 128 to add decimal point on display
    {
        value += 128;
    }
    writeData((digit + 0x34), value); // write data to each digit
}

void TM1650init()
{
    writeData(0x24, 1); // enable the display
    TM1650_setDigit(0, 32, 0); // initialize each digit
    TM1650_setDigit(1, 32, 0); // ...
    TM1650_setDigit(2, 32, 0); // ...
    TM1650_setDigit(3, 32, 0); // ...
}

void putch(char holder)
{
    if(holder == '\r') // if '\r' detected don't shift to another digit
    {
        tab = 0;
    }
    else { // if '\r' not detected shift values to first digit, second digit, ...
        TM1650_setDigit(tab, holder, 0);
        tab++;
        if(tab == 4)
        {
            tab = 0;
            __delay_ms(100);
        }
    }
}

void TM1650_fastPrintNum(uint16_t num) {
    int arr[4];
    arr[3] = num % 10 + 48;
    arr[2] = (num/10) % 10 + 48;
    arr[1] = (num/100) % 10 + 48;
    arr[0] = (num/1000) % 10 + 48;
    
    for(int i = 0; i <= 3; i++) {
        TM1650_setDigit(i, arr[i], 0);
    }
}