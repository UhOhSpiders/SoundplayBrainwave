#pragma once

// number of LEDs in the LED strip
#define LEDCOUNT 300

// SpringAnimator constants
#define SPRING_MASS 100
#define SPRING_GRAVITY -5
#define SPRING_YOYO_FORCE -10 // defines an extra force to bring the spring down faster if its button is pressed while it's midair 
#define SPRING_MAX_HEIGHT 30 // how long the spring is
#define SPRING_MAX_FORCE 36