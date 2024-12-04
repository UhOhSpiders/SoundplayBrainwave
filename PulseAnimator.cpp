#include "PulseAnimator.h"
#include <Arduino.h>

PulseAnimator::PulseAnimator() : held{false, false}, tailBrightnessValues{9, 8, 7, 4, 2, 0}, colorIndexes{1, 2}, tailIndex{0, 0}
{
    init();
}

void PulseAnimator::init()
{
    createBlankArray(leftToRightArray);
    createBlankArray(rightToLeftArray);
    createBlankArray(renderArray);
}

void PulseAnimator::createBlankArray(int array[30][2])
{
    for (int i = 0; i < 30; i++)
    {
        array[i][0] = 0;
        array[i][1] = 0;
    }
}

void PulseAnimator::update()
{
    animateArray(leftToRightArray, 0);
    animateArray(rightToLeftArray, 1);
    overlayArrays(leftToRightArray, rightToLeftArray);
}

void PulseAnimator::animateArray(int arr[30][2], int vector)
{
    if (held[vector])
    {
        arr[0][0] = colorIndexes[vector];
        arr[0][1] = tailBrightnessValues[0];
    }
    else if (tailIndex[vector] < 6 && !held[vector])
    {
        arr[0][0] = colorIndexes[vector];
        arr[0][1] = getFadedTailValue(vector);
    }
    else
    {
        arr[0][0] = 0;
        arr[0][1] = 0;
    }
    for (int i = 29; i > 0; i--)
    {
        arr[i][0] = arr[i - 1][0];
        arr[i][1] = arr[i - 1][1];
    }
}

int *PulseAnimator::overlayArrays(int arr[30][2], int arr2[30][2])
{
    for (int i = 0; i < 30; i++)
    {
        renderArray[i][0] = leftToRightArray[i][0] + rightToLeftArray[30 - i - 1][0];

        if (renderArray[i][0] == colorIndexes[0] + colorIndexes[1])
        {
            renderArray[i][1] = tailBrightnessValues[0]; // max brightness
        }
        else
        {
            renderArray[i][1] = leftToRightArray[i][1] + rightToLeftArray[30 - i - 1][1];
        }
    }
    return (int *)renderArray;
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

void PulseAnimator::printRenderArray()
{
    if (held[0])
    {
        Serial.print(">");
    }
    else
    {
        Serial.print("X");
    }
    for (int i = 0; i < 30; i++)
    {
        Serial.print("[");
        Serial.print(renderArray[i][0]);
        Serial.print(", ");
        Serial.print(renderArray[i][1]);
        Serial.print("] ");
    }
    if (held[1])
    {
        Serial.print("<");
    }
    else
    {
        Serial.print("X");
    }
    Serial.println();
}

int *PulseAnimator::getRenderArray()
{
    printRenderArray();
    return (int *)renderArray;
}
