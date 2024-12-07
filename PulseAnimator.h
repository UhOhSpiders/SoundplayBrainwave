#pragma once
#include <Arduino.h>
#include "Constants.h"

class PulseAnimator
{
private:
    bool held[2];
    int tailBrightnessValues[6];
    int colorIndexes[2];
    int tailIndex[2];
    uint8_t leftToRightArray[LEDS][2];
    uint8_t rightToLeftArray[LEDS][2];

public:
    PulseAnimator();
    void toggleHeld(int vector);
    void init();
    void createBlankArray(uint8_t arr[LEDS][2]);
    void animateArray(uint8_t arr[LEDS][2], int vector);
    uint8_t getPixelColorIndex(int i);
    uint8_t getPixelBrightness(int i);
    int getFadedTailValue(int vector);
    void resetTailIndex(int vector);
    void update();
};