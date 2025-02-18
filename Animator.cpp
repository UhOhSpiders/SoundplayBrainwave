#include "Animator.h"
#include "Constants.h"

Animator::Animator() : held{false, false}
{
}

void Animator::toggleHeld(int stripInputIndex)
{
    held[stripInputIndex] = !held[stripInputIndex];
};

void Animator::createBlankArray(uint8_t array[LEDCOUNT][2])
{
    for (int i = 0; i < LEDCOUNT; i++)
    {
        array[i][0] = 0;
        array[i][1] = 0;
    }
}