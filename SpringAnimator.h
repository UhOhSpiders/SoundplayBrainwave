#pragma once
#include <Arduino.h>
#include "Animator.h"
#include "Constants.h"

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
    float position;
    float velocity;
    float acceleration;
    float mass;
    float releaseForce;
    float gravity;
    float damping;
    float yoyo;
    bool yoyoToggle;
    int MAXHEIGHT;
    int height;
    void move();
    void applyForce(float force);
    void boostIfTapped();
    void compress();
    void decompress();
    void checkEdges();
    void updateRenderArray();
};

// spring animator
// spring
// height 20
// position 0
// velocity 0
// acceleration 0
// mass 2
// release 0
// gravity -1
// damping 0.8
//---------------
// .update() !? HARD
// if(buttonHeld && spring.position == 0){
// spring.compress()
//}else if(!held){
// spring.applyForce(release)
// spring.applyForce(gravity)
//}else{
// spring.fade()
//}
//.move()
// .move(){
// velocity += acceleration
// position += velocity
// .checkEdges()
// velocity *= damping
// acceleration * 0 (reset acceleration)
//}
// .applyForce(force){
// appliedForce = force/mass
// acceleration += appliedForce
//}
// .compress(){
//  if(release < 10){
//  release += 1
//  height -= 1
//  }else{
//  return
//}
// .checkEdges(){
// if(position > LEDCOUNT || position < 0){
// velocity *= -1
// velocity *= (damping * 2)
//}
// ----------------------
// .updateRenderArray()
// for (int i = 0; i < spring.height; i++) .... could be nested loop for multiple springs
// {
//     renderArray[spring.position + i] = 1
// }
// ----------------------
