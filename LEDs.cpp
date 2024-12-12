#include "LEDs.h"
#include <Arduino.h>
#include <WS2812Serial.h>
#include "Constants.h"

// LEDs::LEDs(int pin, int color0[3], int color1[3], int color2[3], int color3[3]) : pin(pin), drawingMemory(new byte[LEDS * 3]), displayMemory(new byte[LEDS * 12]), addressableObject(LEDS, displayMemory, drawingMemory, pin, WS2812_GRB)
LEDs::LEDs(int pin, int color0[3], int color1[3], int color2[3], int color3[3], WS2812Serial addressableObject) : pin(pin), addressableObject(addressableObject)
{
    for (int i = 0; i < 3; i++)
    {
        colors[0][i] = color0[i];
        colors[1][i] = color1[i];
        colors[2][i] = color2[i];
        colors[3][i] = color3[i];
    }
    init();
}

void LEDs::init()
{
    Serial.println(pin);
    addressableObject.setBrightness(10);
    addressableObject.begin();
}

void LEDs::render()
{
    pulseAnimator.update();
    for (int i = 0; i < LEDCOUNT; i++)
    {
        int colorIndex = pulseAnimator.getPixelColorIndex(i);
        int *color = colors[colorIndex];
        int brightness = pulseAnimator.getPixelBrightness(i);
        int scaledRed = (color[0] * brightness) / 10;
        int scaledGreen = (color[1] * brightness) / 10;
        int scaledBlue = (color[2] * brightness) / 10;

        addressableObject.setPixel(i, scaledRed, scaledGreen, scaledBlue);
        // print every 5th colorIndex for easier reading in the serial monitor
        if (i % 5 == 0)
        {
            Serial.print(colorIndex);
        }
    }
    addressableObject.show();
    Serial.println();
}