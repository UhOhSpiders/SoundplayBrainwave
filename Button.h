#pragma once
#include <Bounce.h>

class Button
{
public:
    Button(int pin, int vector);
    int pin;
    int vector;
    bool isPressed;
    bool prevState;
    Bounce bounce;
    bool stateHasChanged;
    void init();
    bool read();
    void updateState();
};