# Soundplay Brainwave

## Outline
This repository contains the code for Soundplay Projects interactive MIDI installation powered by a Teensy 4.0 microcontroller, with electronics designed by Roy Fullname Here. 

## Teensyduino IDE Config
* The Teensyduino IDE allows for the Teensy 4.0 to be formatted and recognised as a USB MIDI device through **Tools > USB Type > MIDI**.
* Set the port as follows: **Tools > Port > Teensy Ports > MIDI (Teensy 4.0)**.

## Structure

- Strip
    - Button buttons[2]
    - LEDS
        - PulseAnimator
    - MidiController
    
## Animation 

The animation logic is defined by the `PulseController` class. The state of each pixel is determined through the combination of two arrays - a `leftToRightArray` and a `rightToLeftArray`. Both of these hold color and brightness values and represent animated pulses moving in opposite directions.

With each update call the contents of _both_ arrays are moved one position to the _right_. The starting pixel is then calculated based on the state of the user inputs.

Finally, the index of the desired pixel colour is returned as `leftToRightArray[i][0] + rightToLeftArray[LEDCOUNT - i - 1]`. This line creates the overlapping effect and flips `rightToLeftArray` to create the contrary motion.

## Libraries 

* The buttons are driven by [Bounce](https://www.pjrc.com/teensy/td_libs_Bounce.html). This library makes it easy to reliably read pushbuttons or mechanical sensors which have contacts that "chatter" or "bounce".

* [WS2812Serial](https://www.pjrc.com/non-blocking-ws2812-led-library/) is used to address the LED strips.
* MIDI data is sent with Teensy's [MIDI Library](https://www.pjrc.com/teensy/td_libs_MIDI.html). These functions are run from the `MidiController` class. If the Teensyduino IDE configuration is correct this library is included automatically without an `#include` directive.

## Electronics


