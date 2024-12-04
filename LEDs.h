#pragma once
#include <Arduino.h>
#include <WS2812Serial.h>

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
    void init();
    void render();
    void clearPixel(int i);
    int getIncrement(int vector);
};