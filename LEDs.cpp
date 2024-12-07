#include "LEDs.h"
#include <Arduino.h>
#include <WS2812Serial.h>
#include "Constants.h"

LEDs::LEDs(int pin, int color1[3], int color2[3], int color3[3]) : pin(pin), drawingMemory(new byte[LEDS * 4]), displayMemory(new byte[pixels * 16]), addressableObject(LEDS, displayMemory, drawingMemory, pin, WS2812_GRB)
{
    for (int i = 0; i < 3; i++)
    {

        colors[0][i] = color1[i];
        colors[1][i] = color2[i];
        colors[2][i] = color3[i];
    }
    init();
}

void LEDs::init()
{
    addressableObject.begin();
    addressableObject.setBrightness(10);
}

void LEDs::render()
{
    pulseAnimator.update();
    for (int i = 0; i < LEDS; i++)
    {
        int *color = colors[pulseAnimator.getPixelColorIndex(i)];
        int brightness = pulseAnimator.getPixelBrightness(i);
        int scaledRed = (color[0] * brightness) / 10;
        int scaledGreen = (color[1] * brightness) / 10;
        int scaledBlue = (color[2] * brightness) / 10;

        // Set the pixel color
        addressableObject.setPixel(i, scaledRed, scaledGreen, scaledBlue);
    }
    addressableObject.show();
}