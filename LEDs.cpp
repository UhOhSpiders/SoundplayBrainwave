#include "LEDs.h"
#include <Arduino.h>

LEDs::LEDs(int pin) : pin(pin) {
    init();
}

void LEDs::init(){
    // create display memory
    // create drawing memory 
    // create NUM pixels
    // create WS2812Serial instance? (this could be different depending on RGB or RGBW)
    // create colors based on RGB or RGBW

    // create pulseController for Roy's pulse logic?
        // pulseAnimator would have:
            // color1, 
            // color2, 
            // color3,
            // spriteLength,
            // pulse[]
            // getCollisions()
            // render()
}

void LEDs::animate(int vector)
{
    if (vector == 0)
    {
        Serial.println("left to right");
        
    }else if(vector == 1){
        Serial.println("right to left");
    }
}

