# Soundplay Brainwave

## Outline
This repository contains the code for Soundplay Projects' Brainwave. This is an interactive MIDI installation powered by a Teensy 4.0 microcontroller, with electronics designed by Roy Shearer & Bal Cooke. 

## Teensyduino IDE Config
* Adjust the Teensyduino IDE settings as follows to allow for the Teensy 4.0 to be read as a USB MIDI device: **Tools > USB Type > MIDI**.
* Set the port: **Tools > Port > Teensy Ports > MIDI (Teensy 4.0)**.

## Structure

The logic is separated into classes. 
- **`Strip`** represents the entire assembly. It is composed of two `Button` objects, a `MidiController` and an `LEDS` object. A new `Strip` can be instantiated in the `Brainwave.ino` file and has an `.update()` method which should be called from within the `Brainwave.ino` loop. 

    - **`Button`** objects handle user input and use `.updateState()` to check if a button is held down or has just been pressed.

    - **`MidiController`** only needs to play one note to trigger an external Pure Data synth. Each `Button` plays on a different channel.

    - **`LEDS`** sends data to the LED strip and renders the animation based on the user inputs. The animation logic itself is factored out into a `PulseController` class, which is described in further detail below. The `.render()` method loops through each pixel, and uses the `PulseController`'s `.getPixelColorIndex(<pixelIndex>)` to get the colour for each pixel on the LED strip. This index is then used to set the correct values from an array of RGB colours. A similar approach is used with `.getPixelBrightness(<pixelIndex>)` to adjust the brightness of each pixel and add a faded tail effect to the pulse.
        - **`PulseController`** manages the custom animation logic through the manipulation of two arrays - `leftToRightArray` and  `rightToLeftArray`. Both of these hold color and brightness values for each of the pixels on the strip. They represent animated pulses moving in opposite directions. Both arrays are treated identically for as long as possible.
        
            With each `.update()` their contents are moved one position to the right using `.animateArray()`.  
            
            Their starting pixels are then calculated based on the state of the user inputs with `.updateStartingPixel()`. This function continues to add to the length of the pulse if the button is held, adds a tail onto the end if the button is released, or simply adds a blank pixel if there is no tail left to draw.

            Finally, the index of the desired pixel colour is returned as `leftToRightArray[i][0] + rightToLeftArray[LEDCOUNT - i - 1][0]`. This line creates the overlapping effect and **_flips_** `rightToLeftArray` to create the contrary motion. The `LEDS` object can then use this value to index its array of given colours and set the pixel accordingly. 

## Libraries 

* The buttons are debounced using [Bounce](https://www.pjrc.com/teensy/td_libs_Bounce.html). This library makes it easy to reliably read pushbuttons or mechanical sensors which have contacts that "chatter" or "bounce".

* [WS2812Serial](https://www.pjrc.com/non-blocking-ws2812-led-library/) is used to address the LED strips.

* MIDI data is sent with Teensy's [MIDI Library](https://www.pjrc.com/teensy/td_libs_MIDI.html). If the Teensyduino IDE configuration is correct then this library is included automatically without any `#include` directive.


