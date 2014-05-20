#include <wiringPi.h>

#include "../include/LEDMatrix.h"

int main(int argc, char *argv[]) {

    short k;

    if (wiringPiSetup() < 0) {
        fprintf(stderr, "setup failed\n");
        exit(1);
    }

    LEDMatrix *lm = new LEDMatrix(2);
    
    lm->print("Hello World");

	//~ for (;;)
	{
		delay(100);

		// shifting to the left
		for (k = 0; k < 100; k++) {
			lm->shiftLeft();
			lm->flip();
			delay(40);
		}
	}
    return 0;
}


