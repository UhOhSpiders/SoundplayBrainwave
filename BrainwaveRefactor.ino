#include "Strip.h"
#include "Button.h"
#include "LEDs.h"
#include "MidiController.h"
#include <tuple>

// button(pin, "vector") "vector" is 1 or 0 and denotes which end of the LED strip the animated light trail starts from. 
Button button1 = Button(16, 0);
Button button2 = Button(17, 1);

// colors for LED strip
std::tuple red = {
    255, 0, 0};
std::tuple green = {
    0, 255, 0};
std::tuple blue = {
    0, 0, 255};

// leds(data pin, pixels, color1, color2, color3)
LEDs leds = LEDs(1, 300, red, green, blue);
// midi(channel1, channel2)
MidiController midiController = MidiController(1, 2);
Strip strip1 = Strip(button1, button2, leds, midiController);

void setup()
{
}

void loop()
{
    strip1.update();
}