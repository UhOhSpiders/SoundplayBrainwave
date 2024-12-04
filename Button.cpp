#include "Button.h"
#include <Arduino.h>

Button::Button(int pin, int vector) : pin(pin), vector(vector), isPressed(false), prevState(false), bounce(Bounce(pin, 5)), stateHasChanged(false)
{
    init();
}

int Button::getPin()
{
    return pin;
}

bool Button::read()
{
    if (bounce.update())
    {
        if (bounce.fallingEdge())
        {
            isPressed = true;
        }
        if (bounce.risingEdge())
        {
            isPressed = false;
        }
    }
    updateState();
    return isPressed;
}

void Button::updateState(){
if(isPressed != prevState){
    prevState = isPressed;
    stateHasChanged = true;
}else{
    stateHasChanged = false;
}
}

void Button::init()
{
    pinMode(pin, INPUT_PULLUP);
    Serial.begin(57600);
    Serial.println("init runs");
}