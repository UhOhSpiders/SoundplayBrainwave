#include "Strip.h"
#include <Arduino.h>

Strip::Strip(Button &button1, Button &button2, LEDs &leds, MidiController midiController) : buttons{button1, button2}, leds(leds), midiController(midiController) {}

void Strip::update()
{
    for (int i = 0; i < 2; i++)
    {
        buttons[i].read();
        if (!buttons[i].isPressed && !buttons[i].stateHasChanged)
        {
            continue;
        }
        else if (buttons[i].isPressed && buttons[i].stateHasChanged)
        {
            midiController.startNote(i);
            pulseAnimator.resetTailIndex(i);
            pulseAnimator.toggleHeld(i);
        }
        else if (!buttons[i].isPressed)
        {
            pulseAnimator.toggleHeld(i);
            midiController.stopNote(i);
        }
    }
    pulseAnimator.update();
    int *renderArray = pulseAnimator.getRenderArray();
    // leds.render(renderArray)
    leds.render();
}


