#pragma once
#include "Button.h"
#include "LEDs.h"
class Strip
{
private:
    Button button1;
    Button button2;
    LEDs LEDController;

public:
    Strip(Button &button1, Button &button2, LEDs &LEDController);
    void update();
};