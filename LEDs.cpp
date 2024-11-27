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
    // pulseController.updatePulses();
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
            int vector = pulseController.pulses[i].vector;       // get vector
            int increment = getIncrement(vector);
            bool collision = pulseController.pulses[i].collision; // get collision state
            Pulse collidingPulse = pulseController.pulses[pulseController.pulses[i].colliding];
            for (int d = 0; d < sampleDuration; d++)
            { // print duration
                if (collision)
                {
                    if (pulseController.pulses[i].crossoverZone(d, collidingPulse))
                    { // check if this pixel is within the
                      // collision colours? colour3
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
            int vector = pulseController.pulses[i].vector;       // get vector
            int increment = getIncrement(vector);
            bool collision = pulseController.pulses[i].collision; // get collision state
            Pulse collidingPulse = pulseController.pulses[pulseController.pulses[i].colliding];
            for (int d = 0; d < sampleDuration; d++)
            { // print duration
                if (collision)
                {
                    if (pulseController.pulses[i].crossoverZone(d, collidingPulse))
                    { // check if this pixel is within the
                      // collision colours? colour3
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
                clearPixel(position + sampleDuration + 1); // clear trailing pixel
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
                    if (pulseController.pulses[i].crossoverZone(k + sampleDuration, collidingPulse))
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
                clearPixel(position + sampleDuration); // clear trailing pixel
            }
        }
    }
    addressableObject.show(); // This sends the updated pixel colors to the hardware.
}

void LEDs::render2()
{
    pulseController.updatePulses();

    for (int j = 0; j < pixels; j++)
    {                                                   // step through each sample
        int pixel = pulseController.pulses[j].position; // get index no
        if (pulseController.pulses[j].active)
        { // check if sample is active

            int sampleDuration = pulseController.pulses[j].hold;  // get duration
            int velocity = pulseController.pulses[j].velocity;    // get velocity
            int vector = pulseController.pulses[j].vector;        // get vector
            bool collision = pulseController.pulses[j].collision; // get collision state
            Pulse collidingPulse = pulseController.pulses[pulseController.pulses[j].colliding];

            // initialise colour variables
            int red = 0;
            int green = 0;
            int blue = 0;
            int white = 0;

            // get the colours from the collision palette
            int redC = 70;
            int greenC = 70;
            int blueC = 70;
            int whiteC = 70;

            if (vector == 0)
            {

                // get colours from palette A
                int red = 50;
                int green = 50;
                int blue = 50;
                int white = 50;

                for (int d = 0; d < sampleDuration; d++)
                { // print duration
                    if (collision)
                    {
                        if (pulseController.pulses[j].crossoverZone(d, collidingPulse))
                        { // check if this pixel is within the crossover zone (offset position, index of colliding pulse)
                            red = 30;
                            green = 30;
                            blue = 30;
                            white = 30;
                        }
                        else
                        {
                            red = 80;
                            green = 80;
                            blue = 80;
                            white = 80;
                        }
                    }
                    int position = pixel - d;
                    addressableObject.setPixel(position, red, green, blue, white); // set this pixel
                    clearPixel(pixel - sampleDuration - 1);     // clear trailing pixel
                }

                // print trailing sprite

                for (int k = 0; k < pulseController.spriteLength; k++)
                { // print end sprite
                    int red = 50;
                    int green = 50;
                    int blue = 50;
                    int white = 50;
                    if (collision)
                    {
                        if (pulseController.pulses[j].crossoverZone(k + sampleDuration, collidingPulse))
                        { // check if this pixel is within the crossover zone
                            red = 120;
                            green = 120;
                            blue = 120;
                            white = 120;
                        }
                        else
                        {
                            red = 50;
                            green = 50;
                            blue = 50;
                            white = 50;
                        }
                    }
                    // set pixel colour based on sprite shape and sample colour values
                    int position = pixel - k - sampleDuration;
                    addressableObject.setPixel(position, red, green, blue, white);
                    clearPixel(position - 1); // clear trailing pixel
                }
            }

            if (vector == 1)
            {
                // print hold/duration/sustain
                int red = 65;
                int green = 65;
                int blue = 65;
                int white = 65;
                for (int d = 0; d < sampleDuration; d++)
                { // print duration
                    if (collision)
                    {
                        if (pulseController.pulses[j].crossoverZone(-d, collidingPulse))
                        { // check if this pixel is within the crossover zone
                            red = 85;
                            green = 85;
                            blue = 85;
                            white = 85;
                        }
                        else
                        {
                            red = 85;
                            green = 85;
                            blue = 85;
                            white = 85;
                        }
                    }
                    int position = pixel + d;
                    addressableObject.setPixel(position, red, green, blue, white);
                    clearPixel(pixel + sampleDuration + 1); // clear trailing pixel
                }

                // print trailing sprite
                for (int k = 0; k < pulseController.spriteLength; k++)
                { // print end sprite
                    red = 85;
                    green = 85;
                    blue = 85;
                    white = 85;
                    if (collision)
                    {
                        if (pulseController.pulses[j].crossoverZone(-k - sampleDuration, collidingPulse))
                        { // check if this pixel is within the crossover zone
                            red = 85;
                            green = 85;
                            blue = 85;
                            white = 85;
                        }
                        else
                        {
                            red = 85;
                            green = 85;
                            blue = 85;
                            white = 85;
                        }
                    }
                    // set pixel colour based on sprite shape and sample colour values
                    int position = pixel + k + sampleDuration;
                    addressableObject.setPixel(position, red, green, blue, white);
                    clearPixel(position + 1); // clear trailing pixel
                }
            }
        }
        addressableObject.show(); // This sends the updated pixel colors to the hardware.
    }
}
