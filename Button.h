#pragma once
#include <Bounce.h>

class Button
{
public:
    Button(int pin, int vector);
    void init();
    int getPin();
    bool read();
    int pin;
    int vector;
    Bounce bounce;
};