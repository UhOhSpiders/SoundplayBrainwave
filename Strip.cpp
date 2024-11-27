#include "Strip.h"
#include <Arduino.h>

Strip::Strip(Button &button1, Button &button2, LEDs &leds, MidiController midiController) : buttons{button1, button2}, leds(leds), midiController(midiController) {}

void Strip::update()
{
    for (int i = 0; i < 2; i++)
    {
        buttons[i].read();
        if(!buttons[i].currentState && !buttons[i].stateHasChanged){
            continue;
        }
        else if (buttons[i].currentState && !buttons[i].held)
        {
            midiController.startNote(i);
            leds.pulseController.startPulse();
            Serial.println("button pressed");
        }
        else if (buttons[i].held)
        {
            Serial.println("button held");
            leds.pulseController.holdPulse(buttons[i].vector);
        }
        else if (!buttons[i].currentState)
        {
            midiController.stopNote(i);
            leds.pulseController.releasePulse(buttons[i].vector);
            Serial.println("button released");
        }
    }
    // leds.render();
}
