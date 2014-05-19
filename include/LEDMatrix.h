/* 
 * File:   LedMatrix.h
 * Author: hikaru
 *
 * Created on May 19, 2014, 10:23 AM
 */

#ifndef LEDMATRIX_H
#define	LEDMATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include <string.h>
//#include "../include/font.h"

#define CS0		10
#define DIN		12
#define CLK		14

#define REG_NOOP 	0x00
#define REG_DECODE 	0x09
#define REG_INTENSITY 	0x0A
#define REG_SCAN_LIMIT 	0x0B
#define REG_SHUTDOWN 	0x0C
#define REG_TEST 	0x0F
#define INTENSITY 	0x13

#define CHECK_BIT(var, pos) (((var) >> (pos)) & 1)

class LEDMatrix {
public:
    LEDMatrix(u_int8_t chips);
    //    LedMatrix(const LedMatrix& orig);
    virtual ~LEDMatrix();

    void latch();
    void clear();
    int write(u_int8_t reg, u_int8_t data);
    void flip(short offset);


private:

    u_int8_t iNumOfChips;
    u_int16_t columns;
    char *buffer;

};

#endif	/* LEDMATRIX_H */

