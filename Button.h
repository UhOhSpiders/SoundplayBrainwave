#pragma once
#include <Bounce.h>

class Button
{
public:
    Button(int pin, int vector);
    int pin;
    int vector;
    bool currentState;
    bool prevState;
    bool held;
    Bounce bounce;
    bool stateHasChanged;
    void init();
    int getPin();
    bool read();
    void updateState();
};