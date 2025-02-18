#pragma once
#include "Button.h"
#include "LEDs.h"
#include "MidiController.h"

class Strip
{
private:
    Button buttons[2];
    LEDs leds;
    MidiController midiController;

public:
    Strip(Button &button1, Button &button2, LEDs &leds, MidiController midiController);
    void update();
};