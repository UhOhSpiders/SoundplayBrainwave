#include "LEDs.h"
#include <Arduino.h>
#include <WS2812Serial.h>

LEDs::LEDs(int pin, int pixels, std::tuple<int, int, int> color1, std::tuple<int, int, int> color2, std::tuple<int, int, int> color3) : pin(pin), pixels(pixels), color1(color1), color2(color2), color3(color3), drawingMemory(new byte[pixels * 4]), displayMemory(new byte[pixels * 16]), addressableObject(pixels, displayMemory, drawingMemory, pin, WS2812_GRB), pulseController(pixels)
{
    init();
}

void LEDs::init()
{
    addressableObject.begin();
    addressableObject.setBrightness(10);
    pulseController.createPulses();
}

void LEDs::clearPixel(int i)
{
    addressableObject.setPixel(i, 0, 0, 0);
}

int LEDs::getIncrement(int vector)
{
    if (vector == 1)
    {
        return 1;
    }
    else if (vector == 0)
    {
        return -1;
    }
}

void LEDs::render()
{
    pulseController.updatePulses();
    for (int i = 0; i < pixels; i++)
    {
        int red = 0;
        int green = 0; // step through each sample
        int blue = 0;
        int white = 0;
        int pixel = pulseController.pulses[i].position; // get index no
        if (pulseController.pulses[i].active && pulseController.pulses[i].vector == 0)
        { // check if sample is active

            int sampleDuration = pulseController.pulses[i].hold;
            int vector = pulseController.pulses[i].vector;        // get vector
            bool collision = pulseController.pulses[i].collision; // get collision state
            Pulse collidingPulse = pulseController.pulses[pulseController.pulses[i].colliding];
            for (int d = 0; d < sampleDuration; d++)
            { // print duration
                int position = pixel - d;
                addressableObject.setPixel(position, red, green, blue, white);
                clearPixel(position + sampleDuration + 1); // clear trailing pixel
            }
            // print trailing sprite
            int spriteLength = pulseController.spriteLength;
            for (int k = 0; k < spriteLength; k++)
            { // print end sprite
                red = std::get<0>(color1);
                green = std::get<1>(color1);
                blue = std::get<2>(color1);
                if (collision)
                {
                    if (pulseController.pulses[i].crossoverZone(k + sampleDuration, collidingPulse))
                    { // check if this pixel is within the crossover zone
                        red = std::get<0>(color3);
                        green = std::get<1>(color3);
                        blue = std::get<2>(color3);
                    }
                    else
                    {
                        red = std::get<0>(color1);
                        green = std::get<1>(color1);
                        blue = std::get<2>(color1);
                    }
                }
                // set pixel colour based on sprite shape and sample colour values
                int position = pixel - k - sampleDuration;
                addressableObject.setPixel(position, red, green, blue, white);
                clearPixel(position - sampleDuration - 1); // clear trailing pixel
            }
        }
        if (pulseController.pulses[i].active && pulseController.pulses[i].vector == 1)
        { // check if sample is active

            int sampleDuration = pulseController.pulses[i].hold;
            int vector = pulseController.pulses[i].vector;        // get vector
            bool collision = pulseController.pulses[i].collision; // get collision state
            Pulse collidingPulse = pulseController.pulses[pulseController.pulses[i].colliding];
            for (int d = 0; d < sampleDuration; d++)
            { // print duration
                if (collision)
                {
                    if (pulseController.pulses[i].collision)
                    { // check if this pixel is within the
                        // collision colours? colour3
                        Serial.println("collisionnnnn");
                        red = std::get<0>(color3);
                        green = std::get<1>(color3);
                        blue = std::get<2>(color3);
                    }
                    else
                    {
                        red = std::get<0>(color2);
                        green = std::get<1>(color2);
                        blue = std::get<2>(color2);
                    }
                }
                int position = pixel - d;
                addressableObject.setPixel(position, red, green, blue, white);
                clearPixel(position + sampleDuration + 2); // clear trailing pixel
            }
            // print trailing sprite
            int spriteLength = pulseController.spriteLength;
            for (int k = 0; k < spriteLength; k++)
            { // print end sprite
                red = std::get<0>(color2);
                green = std::get<1>(color2);
                blue = std::get<2>(color2);
                if (collision)
                {
                    if (pulseController.pulses[i].colliding)
                    { // check if this pixel is within the crossover zone
                        red = std::get<0>(color3);
                        green = std::get<1>(color3);
                        blue = std::get<2>(color3);
                    }
                    else
                    {
                        red = std::get<0>(color2);
                        green = std::get<1>(color2);
                        blue = std::get<2>(color2);
                    }
                }
                // set pixel colour based on sprite shape and sample colour values
                int position = pixel + k + sampleDuration;
                addressableObject.setPixel(position, red, green, blue, white);
                clearPixel(position + sampleDuration + 2); // clear trailing pixel
            }
        }
    }
    addressableObject.show(); // This sends the updated pixel colors to the hardware.
}