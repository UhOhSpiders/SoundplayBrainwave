#include "Button.h"
#include <Arduino.h>

Button::Button(int pin) : pin(pin), isPressed(false), prevState(false), bounce(Bounce(pin, 5)), stateHasChanged(false)
{
    init();
}

bool Button::read()
{
    if (bounce.update())
    {
        if (bounce.fallingEdge())
        {
            isPressed = true;
            Serial.println("held");
        }
        if (bounce.risingEdge())
        {
            isPressed = false;
            Serial.println("not held");
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
}