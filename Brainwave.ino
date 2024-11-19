#include "Strip.h"
#include "Button.h"
#include "LEDs.h"

Button button1 = Button(16, 0);
Button button2 = Button(17, 1);
LEDs leds = LEDs(1);
Strip strip1 = Strip(button1, button2, leds);

void setup()
{
}

// the loop function runs over and over again forever
void loop()
{
    strip1.update()
}