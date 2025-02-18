#pragma once
#include <Arduino.h>
#include "Animator.h"
#include "Constants.h"

struct Spring {
    int position;
    float velocity;
    float acceleration;
    float releaseForce;
    bool yoyoToggle;
    int height;
    int colorIndex;
};

class SpringAnimator : public Animator
{
public:
    SpringAnimator();
    void init() override;
    void update() override;
    uint8_t getPixelColorIndex(int i) override;
    uint8_t getPixelBrightness(int i) override;
private:
    uint8_t renderArray[LEDCOUNT][2];
    Spring spring1;
    Spring spring2;
    void initSpring(Spring &spring, int colorIndex);
    void animateSpring(Spring &spring, int inputIndex);
    void move(Spring &spring);
    void applyForce(Spring &spring, float force);
    void boostIfTapped(Spring &spring);
    void compress(Spring &spring);
    void decompress(Spring &spring);
    void checkEdges(Spring &spring);
    void updateArray(uint8_t renderArray[LEDCOUNT][2]);
};