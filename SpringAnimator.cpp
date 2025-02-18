#include <Arduino.h>
#include "SpringAnimator.h"
#include <cmath>

SpringAnimator::SpringAnimator()
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
}

void SpringAnimator::update()
{
    animateSpring(spring1, 0);
    animateSpring(spring2, 1);
    updateArray(renderArray);
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
            applyForce(spring, SPRING_YOYO_FORCE);
        }
        decompress(spring);
        applyForce(spring, spring.releaseForce);
        if (spring.position > 1)
        {
            applyForce(spring, SPRING_GRAVITY);
        }
        move(spring);
    }
}

void SpringAnimator::applyForce(Spring &spring, float force)
{
    spring.acceleration += force / SPRING_MASS;
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
        spring.releaseForce = SPRING_MAX_FORCE / 2;
    }
}

void SpringAnimator::compress(Spring &spring)
{
    boostIfTapped(spring);
    if (spring.releaseForce < SPRING_MAX_FORCE)
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
    if (spring.height < SPRING_MAX_HEIGHT)
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
    }
}

void SpringAnimator::updateArray(uint8_t renderArray[LEDCOUNT][2])
{
    createBlankArray(renderArray);
    for (int i = 0; i < spring1.height; i++)
    {   
        int roundedPostion = round(spring1.position);
        renderArray[roundedPostion + i][0] = spring1.colorIndex;
        renderArray[roundedPostion + i][1] = 10;
    }
    for (int j = 0; j < spring2.height; j++)
    {   
        int roundedPostion = round(spring2.position);
        renderArray[roundedPostion + j][0] += spring2.colorIndex;
        renderArray[roundedPostion + j][1] = 10;
    }
}

uint8_t SpringAnimator::getPixelBrightness(int i)
{
    return 10;
}

uint8_t SpringAnimator::getPixelColorIndex(int i)
{
    return renderArray[i][0];
}
