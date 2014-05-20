/* 
 * File:   LEDMatrix.h
 * Author: Brian Ho <brian@codeforart.com>
 *
 * Created on May 19, 2014, 10:23 AM
 */

#ifndef LEDMATRIX_H
#define	LEDMATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>


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
	LEDMatrix(u_int8_t DIN, u_int8_t CS0, u_int8_t CLK, u_int8_t chips);
    
    //    LedMatrix(const LedMatrix& orig);
    virtual ~LEDMatrix();

    void latch();
    void clear();
    int write(u_int8_t reg, u_int8_t data);
    void flip();
    void shiftLeft(short offset=1);
    void shiftRight(short offset=1);
    void print(char* s);
    
    
    
    u_int16_t columns;

private:

	u_int8_t CS0 = 10, DIN = 12, CLK = 14;

    u_int8_t iNumOfChips;
    char *buffer;
    short offset = 0;

};

#endif	/* LEDMATRIX_H */

