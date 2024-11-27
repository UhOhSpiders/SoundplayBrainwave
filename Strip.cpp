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
        else if (buttons[i].currentState && buttons[i].stateHasChanged)
        {
            midiController.startNote(i);
            leds.pulseController.startPulse(buttons[i].vector);
            Serial.println(buttons[i].vector);
        }
        else if (buttons[i].held)
        {
            leds.pulseController.holdPulse(buttons[i].vector);
        }
        else if (!buttons[i].currentState)
        {
            midiController.stopNote(i);
        }
    }
    leds.pulseController.updatePulses();
    leds.render();
}
