#include <Arduino.h>
#include "SpringAnimator.h"
#include <cmath>

SpringAnimator::SpringAnimator() : position(0), velocity(0), acceleration(0), mass(1), releaseForce(0), gravity(-3), yoyo(-25), yoyoToggle(false), damping(0), height(30), MAXHEIGHT(30)
{
    init();
}

void SpringAnimator::init()
{
    createBlankArray(renderArray);
}

void SpringAnimator::update()
{
    if (held[0] && position > 1)
    {
        yoyoToggle = true;
    }
    if (held[0] && position < 1)
    {
        compress();
    }
    if (!held[0])
    {
        // if (yoyoToggle)
        // {
        //     applyForce(yoyo);
        // }
        decompress();
        applyForce(releaseForce);
        if (position > 1)
        {

            applyForce(gravity);
        }
        move();
    }
    // Serial.println(releaseForce);
    // Serial.println();
    updateRenderArray();
}

void SpringAnimator::applyForce(float force)
{
    acceleration += force / mass;
}

void SpringAnimator::move()
{
    velocity += acceleration;
    position += velocity;
    checkEdges();
    acceleration = 0;
}

void SpringAnimator::boostIfTapped()
{
    if (releaseForce < 2)
    {
        releaseForce = 10;
    }
}

void SpringAnimator::compress()
{
    // boostIfTapped();
    // add min height
    if (releaseForce < 15)
    {
        releaseForce += 1;
    }
    if (height > 3)
    {
        height -= 1;
    }
}

void SpringAnimator::decompress()
{

    releaseForce -= 0.8;
    if (releaseForce < 1)
    {
        releaseForce = 0;
    }
    if (height < MAXHEIGHT)
    {
        height += 4;
    }
}

void SpringAnimator::checkEdges()
{
    if (position < 0)
    {
        position = 0;
        releaseForce *= -1;
        yoyoToggle = false;
    }
    else if (position > LEDCOUNT - height)
    {
        position = LEDCOUNT - height;
        releaseForce *= -1;
        Serial.println("bounce");
    }
}

void SpringAnimator::updateRenderArray()
{
    createBlankArray(renderArray);
    for (int i = 0; i < height; i++)
    {
        // add range check and round down the floats
        int roundedPosition = round(position);
        renderArray[0][roundedPosition + i] = 1;
    }
}

uint8_t SpringAnimator::getPixelBrightness(int i)
{
    return renderArray[1][i];
}

uint8_t SpringAnimator::getPixelColorIndex(int i)
{
    return renderArray[0][i];
}
