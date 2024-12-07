#pragma once
#include <Arduino.h>
#include <WS2812Serial.h>
#include "PulseAnimator.h"

#include <tuple>

class LEDs
{
public:
    LEDs(int pin,  int color1[3], int color2[3], int color3[3]);
    int pin;
    int pixels;
    int colors[3][3];
    byte *drawingMemory;
    byte *displayMemory;
    WS2812Serial addressableObject;
    PulseAnimator pulseAnimator;
    void init();
    void render();
    void clearPixel(int i);
};