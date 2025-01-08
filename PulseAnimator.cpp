#include "PulseAnimator.h"
#include <Arduino.h>

PulseAnimator::PulseAnimator() : held{false, false}, tailBrightnessValues{10, 2, 2, 2, 2, 1}, colorIndexes{1, 2}, tailIndex{0, 0}
{
    init();
}

void PulseAnimator::init()
{
    createBlankArray(leftToRightArray);
    createBlankArray(rightToLeftArray);
}

void PulseAnimator::createBlankArray(uint8_t array[LEDCOUNT][2])
{
    for (int i = 0; i < LEDCOUNT; i++)
    {
        array[i][0] = 0;
        array[i][1] = 0;
    }
}

void PulseAnimator::update()
{
    animateArray(leftToRightArray);
    animateArray(rightToLeftArray);
    updateStartingPixel(leftToRightArray,0);
    updateStartingPixel(rightToLeftArray,1);
}

void PulseAnimator::animateArray(uint8_t arr[LEDCOUNT][2])
{
    // move everything in the array along 1
    for (int i = LEDCOUNT - 1; i > 0; i--)
    {
        arr[i][0] = arr[i - 1][0];
        arr[i][1] = arr[i - 1][1];
    }
}

void PulseAnimator::updateStartingPixel(uint8_t arr[LEDCOUNT][2], int stripInputIndex){
    // if the button/input is held, use the appropriate color (based on stripInputIndex) at full brightness
    if (held[stripInputIndex])
    {
        arr[0][0] = colorIndexes[stripInputIndex];
        arr[0][1] = tailBrightnessValues[0];
    }
    // if the button/input is released and there is still tail left to render, add the next pixel of tail
    else if (tailIndex[stripInputIndex] < 6 && !held[stripInputIndex])
    {
        arr[0][0] = colorIndexes[stripInputIndex];
        arr[0][1] = getFadedTailValue(stripInputIndex);
    }
    // if all the tail has been drawn and the button/input isn't held, leave the starting pixel blank
    else
    {
        arr[0][0] = 0;
        arr[0][1] = 0;
    }
}

uint8_t PulseAnimator::getPixelColorIndex(int i)
{
    // rightToLeftArray[NUMPIXELS - i - 1][0] <- this indexing works backwards through the rtL array, effectively flipping the animation
    // up until this point .animateArray() has been moving both leftToRightArray & rightToLeftArray in the same direction with each .update() call
    // We can add this flipped rtL value to the leftToRightArray to get an overlapping effect, and to make the pulses move in opposite directions. eg a pixel occupied by an active lTR pulse (colorIndex of 1) and rTL pulse (colorIndex of 2) will result in a combined colorIndex of 3.
    uint8_t colorIndex = leftToRightArray[i][0] + rightToLeftArray[LEDCOUNT - i - 1][0];
    return colorIndex;
}

uint8_t PulseAnimator::getPixelBrightness(int i)
{
    uint8_t brightness;
    // rightToLeftArray[NUMPIXELS - i - 1][0] <- Same flip from getPixelColorIndex happens here. This indexing works backwards through the array, effectively flipping the animation
    if (leftToRightArray[i][0] + rightToLeftArray[LEDCOUNT - i - 1][0] == colorIndexes[0] + colorIndexes[1])
    {
        brightness = tailBrightnessValues[0]; // if ltR and rtL overlap then set brightness to max
    }
    else
    {
        brightness = leftToRightArray[i][1] + rightToLeftArray[LEDCOUNT - i - 1][1]; // if there's no overlap just leave as is
    }
    return brightness;
}

void PulseAnimator::resetTailIndex(int stripInputIndex)
{
    tailIndex[stripInputIndex] = 0;
}

int PulseAnimator::getFadedTailValue(int stripInputIndex)
{
    return tailBrightnessValues[tailIndex[stripInputIndex]++];
};

void PulseAnimator::toggleHeld(int stripInputIndex)
{
    held[stripInputIndex] = !held[stripInputIndex];
}