#pragma once
#include "PulseController.h"
#include <Arduino.h>
#include <WS2812Serial.h>
#include "Pulse.h"
#include <tuple>

class LEDs
{
public:
    LEDs(int pin, int pixels, std::tuple<int,int,int> color1,std::tuple<int,int,int> color2,std::tuple<int,int,int> color3);
    int pin;
    int pixels;
    std::tuple<int,int,int> color1;
    std::tuple<int,int,int> color2;
    std::tuple<int,int,int> color3;
    byte *drawingMemory;
    byte *displayMemory;
    WS2812Serial addressableObject;
    PulseController pulseController;
    void init();
    void render();
    void render2();
    // void renderTail(Pulse &pulse);
    void clearPixel(int i);
    int getIncrement(int vector);
};