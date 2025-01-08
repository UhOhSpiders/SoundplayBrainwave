#include "Strip.h"
#include "Button.h"
#include "LEDs.h"
#include "MidiController.h"
#include "Constants.h"
#include <WS2812Serial.h>

Button button1 = Button(16);
Button button2 = Button(17);
Button button3 = Button(18);
Button button4 = Button(19);

int off[3] = {0, 0, 0};
int red[3] = {255, 0, 0};
int green[3] = {0, 255, 0};
int blue[3] = {0, 0, 255};
int yellow[3] = {255, 255, 0};
int cyan[3] = {0, 255, 255};
int magenta[3] = {255, 0, 255};
int orange[3] = {255, 165, 0};
int purple[3] = {128, 0, 128};
int pink[3] = {255, 192, 203};


byte drawingMemory[LEDCOUNT*3];         //  3 bytes per LED
DMAMEM byte displayMemory[LEDCOUNT*12]; // 12 bytes per LED

WS2812Serial ledsObject1(LEDCOUNT, displayMemory, drawingMemory, 1, WS2812_GRB);

byte drawingMemory2[LEDCOUNT*3];         //  3 bytes per LED
DMAMEM byte displayMemory2[LEDCOUNT*12]; // 12 bytes per LED

WS2812Serial ledsObject2(LEDCOUNT, displayMemory2, drawingMemory2, 8, WS2812_GRB);

// CHOOSE COLOURS HERE. (dataPin, offColor, leftToRightPulseColor, rightToLeftPulseColor, overlapColor, addressable WS2812Serial object)
// choose from presets above or make your own in a matching format 
LEDs leds = LEDs(1, off, red, magenta, pink, ledsObject1);
LEDs leds2 = LEDs(8, off, purple, blue, cyan, ledsObject2);

MidiController midiController = MidiController(1, 2);
MidiController midiController2 = MidiController(3, 4);

// the individual components are then assigned to each "strip" here
Strip strip1 = Strip(button1, button2, leds, midiController);
Strip strip2 = Strip(button3, button4, leds2, midiController2);

void setup()
{
    // setup board LED
    pinMode(13, OUTPUT);
}

void loop()
{
    // turn board LED on for troubleshooting purposes
    digitalWrite(13, HIGH);
    // update the strips instantiated above
    strip1.update();
    strip2.update();
}