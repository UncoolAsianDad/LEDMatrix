/*
 * File:   LEDMatrix.cpp
 * Author: Brian Ho <brian@codeforart.com>
 *
 * Created on May 19, 2014, 10:23 AM
 */

#include "../include/LEDMatrix.h"
#include "../include/font.h"

LEDMatrix::LEDMatrix(u_int8_t DIN, u_int8_t CS0, u_int8_t CLK, u_int8_t chips):LEDMatrix(chips) {
	
	this->CS0 = CS0;
	this->DIN = DIN;
	this->CLK = CLK;
	
}

LEDMatrix::LEDMatrix(u_int8_t chips) {
    unsigned short i;

    iNumOfChips = chips;
    columns = 0x100;

    pinMode(CS0, OUTPUT);
    pinMode(DIN, OUTPUT);
    pinMode(CLK, OUTPUT);

    buffer = (char*) malloc(columns);

    for (i = 0; i < columns; i++) {
        buffer[i] = i + 1;
    }

    for (i = 0; i <= iNumOfChips; i++)
        write(REG_SCAN_LIMIT, 0x07);
    latch();

    for (i = 0; i <= iNumOfChips; i++)
        write(REG_DECODE, 0x00);
    latch();

    for (i = 0; i <= iNumOfChips; i++)
        write(REG_SHUTDOWN, 0x01);
    latch();

    for (i = 0; i <= iNumOfChips; i++)
        write(REG_TEST, 0x00);
    latch();

    for (i = 0; i <= iNumOfChips; i++)
        write(REG_INTENSITY, INTENSITY);
    latch();

    clear();

}

/*
LEDMatrix::LEDMatrix(const LEDMatrix& orig) {
}
 */

LEDMatrix::~LEDMatrix() {
    delete buffer;
}

void LEDMatrix::latch(void) {

    digitalWrite(CS0, HIGH);
    delayMicroseconds(1);

    digitalWrite(CS0, LOW);
    delayMicroseconds(1);

}

void LEDMatrix::clear(void) {
    unsigned char i, j;
    
    for (i = 1; i <= 8; i++) {
        for (j = 0; j <= iNumOfChips; j++)
            write(i, 0x00);

        latch();
    }
}

int LEDMatrix::write(u_int8_t reg, u_int8_t data) {
    u_int8_t i = 16;

    unsigned short mot = (reg << 8) | data;

    digitalWrite(CS0, LOW);
    delayMicroseconds(1);

    do {
        digitalWrite(CLK, LOW);
        delayMicroseconds(1);

        digitalWrite(DIN, CHECK_BIT(mot, i - 1));
        delayMicroseconds(1);

        digitalWrite(CLK, HIGH);
        delayMicroseconds(1);

        i--;
    } while (i != 0);

    //~ printf("0x%04X\n", mot);

    delayMicroseconds(1);

    return 0;
}

void LEDMatrix::shiftLeft(short offset) {
	this->offset += offset;
	
	this->offset %= this->columns;

}

void LEDMatrix::shiftRight(short offset) {
	this->offset -= offset;
	
	this->offset %= this->columns;
}


/**
 * Flips the screen over
 * @param offset
 */
void LEDMatrix::flip() {
    char i, j, *ptr;

    for (i = 1; i <= 8; i++) {
        for (j = 0; j < iNumOfChips; j++) {
            ptr = buffer + ((j << 3) | i) - 1;
    
            write(i, *(ptr + offset));
        }
        latch();
    }
    
}
