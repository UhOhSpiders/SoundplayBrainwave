#include "Strip.h"
#include <Arduino.h>

Strip::Strip(Button &button1, Button &button2, LEDs &LEDController) : button1(button1), button2(button2), LEDController(LEDController) {}

void Strip::update()
{
    if (button1.read())
    {
        Serial.println("button 1 pressed");
        LEDController.animate(button1.vector);
    }
    if (button2.read())
    {
        Serial.println("button 2 pressed");
        LEDController.animate(button2.vector);
    }
}
