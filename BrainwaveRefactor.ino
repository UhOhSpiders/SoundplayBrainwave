#include "Strip.h"
#include "Button.h"
#include "LEDs.h"
#include "MidiController.h"
#include <tuple>

// button(pin, "vector") "vector" is 1 or 0 and denotes which end of the LED strip the animated light trail starts from.
Button button1 = Button(16, 0);
Button button2 = Button(17, 1);

// colors for LED strip
std::tuple<int, int, int> red = {255, 0, 0};
std::tuple<int, int, int> green = {0, 255, 0};
std::tuple<int, int, int> blue = {0, 0, 255};
std::tuple<int, int, int> yellow = {255, 255, 0};
std::tuple<int, int, int> cyan = {0, 255, 255};
std::tuple<int, int, int> magenta = {255, 0, 255};
std::tuple<int, int, int> orange = {255, 165, 0};
std::tuple<int, int, int> purple = {128, 0, 128};
std::tuple<int, int, int> pink = {255, 192, 203};

// leds(data pin, pixels, color1, color2, color3)
LEDs leds = LEDs(1, 300, magenta, yellow, green);
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