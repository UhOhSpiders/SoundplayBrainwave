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

    - **`LEDS`** sends data to an LED strip and renders the animation based on the user inputs. Its associated data pin, colors, memory and animation style can be instantiated in the `.ino` file and passed as arguments to an `LEDS` object.

        The core animation logic is defined in an **`Animator`** parent class, and is extended as a **`PulseAnimator`** or a **`SpringAnimator`**. Their behavior is described in further detail below. The `.render()` method loops through each pixel, and uses the `Animator`'s `.getPixelColorIndex(<pixelIndex>)` to get the colour for each pixel on the LED strip. This index is then used to set the correct values from an array of RGB colours. A similar approach is used with `.getPixelBrightness(<pixelIndex>)` to allow for any fading effects that `Animator` may implement.

        - **`PulseAnimator`** manages the animation for the original pulse effect on the Brainwave with a `leftToRightArray` and  `rightToLeftArray`. Both of these hold color and brightness values for each of the pixels on the strip. They represent animated pulses moving in opposite directions. 
        - **`SpringAnimator`** is an optional animation mode for the Brainwave. It's based on [the Vector chapter in Daniel Shiffman's *The Nature of Code*](https://natureofcode.com/vectors/) - although our vector has been simplified down to 1 dimension from his 2D example. It creates two "springs" which overlap without colliding with each other.

## Libraries 

* The buttons are debounced using [Bounce](https://www.pjrc.com/teensy/td_libs_Bounce.html). This library makes it easy to reliably read pushbuttons or mechanical sensors which have contacts that "chatter" or "bounce".

* [WS2812Serial](https://www.pjrc.com/non-blocking-ws2812-led-library/) is used to address the LED strips.

* MIDI data is sent with Teensy's [MIDI Library](https://www.pjrc.com/teensy/td_libs_MIDI.html). If the Teensyduino IDE configuration is correct then this library is included automatically without any `#include` directive.


