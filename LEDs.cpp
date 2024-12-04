#include "LEDs.h"
#include <Arduino.h>
#include <WS2812Serial.h>

LEDs::LEDs(int pin, int pixels, std::tuple<int, int, int> color1, std::tuple<int, int, int> color2, std::tuple<int, int, int> color3) : pin(pin), pixels(pixels), color1(color1), color2(color2), color3(color3), drawingMemory(new byte[pixels * 4]), displayMemory(new byte[pixels * 16]), addressableObject(pixels, displayMemory, drawingMemory, pin, WS2812_GRB)
{
    init();
}

void LEDs::init()
{
    addressableObject.begin();
    addressableObject.setBrightness(10);
}

void LEDs::clearPixel(int i)
{
    addressableObject.setPixel(i, 0, 0, 0);
}


void LEDs::render()
{
    
    addressableObject.show();
}