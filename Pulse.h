#ifndef PULSE_H
#define PULSE_H

#include <Arduino.h>

struct ab {
  int a;
  int b;
};

class Pulse {

  private:
    //    byte pin;

  public:
    Pulse();
    bool active;
    int index;
    int vector;
    int position;
    int hold;
    int end;
    int seed;
    int velocity;
    bool collision;
    bool prevCollision;
    int colliding;

    void init(int, int);
    void trigger(int);
    void sustain();
    void detrigger();
    void expire();
    int update();
    void on();
    void off();
    bool crossoverZone(int, Pulse);
};

#endif
