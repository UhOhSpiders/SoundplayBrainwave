#include <Arduino.h>
#include "SpringAnimator.h"
#include <cmath>

SpringAnimator::SpringAnimator() : mass(100), gravity(-5), yoyo(-10), damping(0), MAXHEIGHT(30), MAXFORCE(36)
{
    init();
}

void SpringAnimator::init()
{
    createBlankArray(renderArray);
    initSpring(spring1, 1);
    initSpring(spring2, 2);
}

void SpringAnimator::initSpring(Spring &spring, int colorIndex)
{
    spring.acceleration = 0;
    spring.height = 30;
    spring.position = 0;
    spring.releaseForce = 0;
    spring.velocity = 0;
    spring.yoyoToggle = false;
    spring.colorIndex = colorIndex;
    createBlankArray(spring.renderArray);
}

void SpringAnimator::update()
{
    animateSpring(spring1, 0);
    animateSpring(spring2, 1);
    updateArray(spring1);
    updateArray(spring2);
}

void SpringAnimator::animateSpring(Spring &spring, int inputIndex)
{
    if (held[inputIndex] && spring.position > 1)
    {
        spring.yoyoToggle = true;
    }
    if (held[inputIndex] && spring.position < 1)
    {
        compress(spring);
    }
    else
    {
        if (spring.yoyoToggle)
        {
            applyForce(spring, yoyo);
        }
        decompress(spring);
        applyForce(spring, spring.releaseForce);
        if (spring.position > 1)
        {
            applyForce(spring, gravity);
        }
        move(spring);
    }
}

void SpringAnimator::applyForce(Spring &spring, float force)
{
    spring.acceleration += force / mass;
}

void SpringAnimator::move(Spring &spring)
{
    spring.velocity += spring.acceleration;
    spring.position += spring.velocity;
    checkEdges(spring);
    spring.acceleration = 0;
}

void SpringAnimator::boostIfTapped(Spring &spring)
{
    if (spring.releaseForce < 2)
    {
        spring.releaseForce = MAXFORCE / 2;
    }
}

void SpringAnimator::compress(Spring &spring)
{
    boostIfTapped(spring);
    if (spring.releaseForce < MAXFORCE)
    {
        spring.releaseForce += 1;
    }
    if (spring.height > 3)
    {
        spring.height -= 1;
    }
}

void SpringAnimator::decompress(Spring &spring)
{

    spring.releaseForce -= 0.8;
    if (spring.releaseForce < 1)
    {
        spring.releaseForce = 0;
    }
    if (spring.height < MAXHEIGHT)
    {
        spring.height += 4;
    }
}

void SpringAnimator::checkEdges(Spring &spring)
{
    if (spring.position < 0)
    {
        spring.position = 0;
        spring.velocity *= -0.8;
        spring.yoyoToggle = false;
    }
    else if (spring.position > LEDCOUNT - spring.height - 2)
    {
        spring.position = LEDCOUNT - spring.height;
        spring.velocity *= -0.8;
        Serial.println("bounce");
        Serial.println(spring.position);
    }
}

void SpringAnimator::updateArray(Spring &spring)
{
    createBlankArray(spring.renderArray);
    for (int i = 0; i < spring.height; i++)
    {   
        int roundedPostion = round(spring.position);
        spring.renderArray[roundedPostion + i][0] = spring.colorIndex;
        spring.renderArray[roundedPostion + i][1] = 10;
    }
}

uint8_t SpringAnimator::getPixelBrightness(int i)
{
    return 10;
}

uint8_t SpringAnimator::getPixelColorIndex(int i)
{
    return spring1.renderArray[i][0] + spring2.renderArray[i][0];
}
