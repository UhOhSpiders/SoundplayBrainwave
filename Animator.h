#pragma once
#include <Arduino.h>
#include "Constants.h"

class Animator
{
private:
public:
    Animator();
    bool held[2];
    virtual void init() = 0;
    virtual void update() = 0;
    virtual uint8_t getPixelColorIndex(int i) = 0;
    virtual uint8_t getPixelBrightness(int i) = 0;
    void createBlankArray(uint8_t arr[LEDCOUNT][2]);
    void toggleHeld(int i);
};