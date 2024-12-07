#include "Strip.h"
#include "Button.h"
#include "LEDs.h"
#include "MidiController.h"
#include "Constants.h"
// button(pin, "vector") "vector" is 1 or 0 and denotes which end of the LED strip the animated light trail starts from when the button is pressed.
Button button1 = Button(16, 0);
Button button2 = Button(17, 1);
Button button3 = Button(18, 0);
Button button4 = Button(19, 1);

// some color options for LED strip
int red[3] = {255, 0, 0};
int green[3] = {0, 255, 0};
int blue[3] = {0, 0, 255};
int yellow[3] = {255, 255, 0};
int cyan[3] = {0, 255, 255};
int magenta[3] = {255, 0, 255};
int orange[3] = {255, 165, 0};
int purple[3] = {128, 0, 128};
int pink[3] = {255, 192, 203};

// leds(data pin, color1, color2, color3)
LEDs leds = LEDs(1, magenta, yellow, green);
LEDs leds2 = LEDs(2, orange, pink, red);

// midi(channel1, channel2)
MidiController midiController = MidiController(1, 2);
MidiController midiController2 = MidiController(3, 4);
Strip strip1 = Strip(button1, button2, leds, midiController);
Strip strip2 = Strip(button3, button4, leds2, midiController2);


void setup()
{
}

void loop()
{
    strip1.update();
    strip2.update();
}