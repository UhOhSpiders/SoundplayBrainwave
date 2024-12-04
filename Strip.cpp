#include "Strip.h"
#include <Arduino.h>

Strip::Strip(Button &button1, Button &button2, LEDs &leds, MidiController midiController) : buttons{button1, button2}, leds(leds), midiController(midiController) {}

void Strip::update()
{
    for (int i = 0; i < 2; i++)
    {
        buttons[i].read();
        if(!buttons[i].isPressed && !buttons[i].stateHasChanged){
            continue;
        }
        else if (buttons[i].isPressed && buttons[i].stateHasChanged)
        {
            midiController.startNote(i);
            // pulseAnimator.held[i] = true;
        }
        else if (!buttons[i].isPressed)
        {
            // pulseAnimator.held[i] = false;
            midiController.stopNote(i);
        }
    }
    // pulseAnimator.update();
    // renderArray = pulseAnimator.getRenderArray();
    // leds.render(renderArray)
    leds.render();
}
