#pragma once
#include <Arduino.h>
#include <WS2812Serial.h>
#include "PulseAnimator.h"

class LEDs
{
private:
    byte *drawingMemory;
    byte *displayMemory;
    WS2812Serial addressableObject;
    void init();
    int colors[4][3];
public:
    LEDs(int pin, int color0[3], int color1[3], int color2[3], int color3[3], WS2812Serial addressableObject);
    PulseAnimator pulseAnimator;
    int pin;
    int pixels;
    void render();
    void clearPixel(int i);
};