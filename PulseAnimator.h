#pragma once
#include <Arduino.h>
#include "Constants.h"
#include "Animator.h"

class PulseAnimator : public Animator
{
private:
    int tailBrightnessValues[6];
    int colorIndexes[2];
    int tailIndex[2];
    uint8_t leftToRightArray[LEDCOUNT][2];
    uint8_t rightToLeftArray[LEDCOUNT][2];
    void animateArray(uint8_t arr[LEDCOUNT][2]);
    void updateStartingPixel(uint8_t arr[LEDCOUNT][2], int stripInputIndex);
    int getFadedTailValue(int stripInputIndex);
    void resetTailIndex(int stripInputIndex);

public:
    PulseAnimator();
    void init() override;
    uint8_t getPixelColorIndex(int i) override;
    uint8_t getPixelBrightness(int i) override;
    void update() override;
};
