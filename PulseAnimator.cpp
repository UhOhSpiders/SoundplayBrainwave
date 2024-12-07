#include "PulseAnimator.h"
#include <Arduino.h>

PulseAnimator::PulseAnimator() : held{false, false}, tailBrightnessValues{10, 8, 7, 4, 2, 0}, colorIndexes{1, 2}, tailIndex{0, 0}
{
    init();
}

void PulseAnimator::init()
{
    createBlankArray(leftToRightArray);
    createBlankArray(rightToLeftArray);
}

void PulseAnimator::createBlankArray(uint8_t array[LEDS][2])
{
    for (int i = 0; i < LEDS; i++)
    {
        array[i][0] = 0;
        array[i][1] = 0;
    }
}

void PulseAnimator::update()
{
    animateArray(leftToRightArray, 0);
    animateArray(rightToLeftArray, 1);
}

void PulseAnimator::animateArray(uint8_t arr[LEDS][2], int vector)
{
    // DECIDE ON THE STARTING PIXEL. 
    // if the button is held, use the appropriate color at full brightness
    if (held[vector])
    {
        arr[0][0] = colorIndexes[vector];
        arr[0][1] = tailBrightnessValues[0];
    }
    // if the button is released and there is still tail left to render, add the next bit of tail
    else if (tailIndex[vector] < sizeof(tailBrightnessValues) && !held[vector])
    {
        arr[0][0] = colorIndexes[vector];
        arr[0][1] = getFadedTailValue(vector);
    }
    // if all the tail has been drawn and the button isn't held, leave the starting pixel blank
    else
    {
        arr[0][0] = 0;
        arr[0][1] = 0;
    }
    // once the starting pixel has been set, move the rest of the array along 1
    for (int i = LEDS - 1; i > 0; i--)
    {
        arr[i][0] = arr[i - 1][0];
        arr[i][1] = arr[i - 1][1];
    }
}

uint8_t  PulseAnimator::getPixelColorIndex(int i)
{
    // rightToLeftArray[NUMPIXELS - i - 1][0] <- this indexing works backwards through the rtL array, effectively flipping the animation 
    // up until this point both leftToRightArray & rightToLeftArray have been moving in the same direction with each .update() call
    // we can then add this flipped rtL value to the leftToRightArray, to get an overlapping effect, and to make the pulses move in opposite directions. A pixel occupied by an active lTR pulse (colorIndex of 1) and rTL pulse (colorIndex of 2) will result in a combined colorIndex of 3.
    uint8_t colorIndex = leftToRightArray[i][0] + rightToLeftArray[LEDS - i - 1][0];
    return colorIndex;
}

uint8_t  PulseAnimator::getPixelBrightness(int i){
        uint8_t brightness;
  // rightToLeftArray[NUMPIXELS - i - 1][0] <- Same flip from getPixelColorIndex happens here. This indexing works backwards through the array, effectively flipping the animation 
        if (leftToRightArray[i][0] + rightToLeftArray[LEDS - i - 1][0] == colorIndexes[0] + colorIndexes[1])
        {
            brightness = tailBrightnessValues[0]; // if ltR and rtL overlap then set brightness to max
        }
        else
        {
            brightness = leftToRightArray[i][1] + rightToLeftArray[LEDS - i - 1][1]; // if there's no overlap just leave as is
        }
        return brightness;
}

void PulseAnimator::resetTailIndex(int vector)
{
    tailIndex[vector] = 0;
}

int PulseAnimator::getFadedTailValue(int vector)
{
    return tailBrightnessValues[tailIndex[vector]++];
};

void PulseAnimator::toggleHeld(int vector)
{
    held[vector] = !held[vector];
}