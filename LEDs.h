#pragma once
#include <Arduino.h>
#include <WS2812Serial.h>
#include "Animator.h"
#include "Constants.h"

class LEDs
{
private:
    byte *drawingMemory;
    byte *displayMemory;
    WS2812Serial addressableObject;
    void init();
    int colors[4][3];

public:
    LEDs(int pin, int color0[3], int color1[3], int color2[3], int color3[3], byte *drawingMem, byte *displayMem, Animator *animator);
    Animator *animator;
    // possible bonus feature to allow animation selection during runtime 
    // Animator[2] *animatorOptions;
    // Animator setAnimationOption(int i);
    int pin;
    int pixels;
    void render();
    void clearPixel(int i);
};