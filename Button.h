#pragma once
#include <Bounce.h>

class Button
{
public:
    Button(int pin);
    int pin;
    bool isPressed;
    bool prevState;
    Bounce bounce;
    bool stateHasChanged;
    void init();
    bool read();
    void updateState();
};