#pragma once

class LEDs
{
    public:
    LEDs(int pin);
    int pin;
    void init();
    void animate(int vector);
};