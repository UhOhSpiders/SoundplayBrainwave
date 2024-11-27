#include "Button.h"
#include <Arduino.h>

Button::Button(int pin, int vector) : pin(pin), vector(vector), currentState(false), prevState(false), held(false), bounce(Bounce(pin, 5)), stateHasChanged(false)
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
            currentState = true;
            held = true;
        }
        if (bounce.risingEdge())
        {
            held = false;
            currentState = false;
        }
    }
    updateState();
    return currentState;
}

void Button::updateState(){
if(currentState != prevState){
    prevState = currentState;
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