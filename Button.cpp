#include "Button.h"
#include <Arduino.h>

Button::Button(int pin, int vector) : pin(pin), vector(vector),bounce(Bounce(pin, 5)) {
    init();
}

int Button::getPin(){
    return pin;
}

bool Button::read(){
    bounce.update();
    return bounce.read();
}

void Button::init(){
    pinMode(pin, INPUT_PULLUP);
}