#include <wiringPi.h>
#include "../include/LEDMatrix.h"

int main(int argc, char *argv[]) {

    short k;

    if (wiringPiSetup() < 0) {
        fprintf(stderr, "setup failed\n");
        exit(1);
    }

    LEDMatrix *lm = new LEDMatrix(2);

    delay(1000);

    printf("Shift Left");
    // shifting to the left
    for (k = 0; k < 0xFF - 16; k++) {
        lm->flip(k);
        delay(10);
    }

    delay(1000);

    printf("Shift Right");
    for (k = 0xFF - 16; k >= 0; k--) {
        lm->flip(k);
        delay(10);
    }


    return 0;
    //

}


