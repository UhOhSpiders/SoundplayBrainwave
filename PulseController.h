#pragma once
#include <vector>
#include "Pulse.h"

class PulseController {
public:
    PulseController(int maxPulses); // Default constructor
    void createPulses();
    void startPulse(int);
    void holdPulse(int);
    void releasePulse(int);
    void updatePulses();
    void collisionDetect(int);
    void render();
    std::vector<Pulse> pulses;
    const int spriteLength = 7; // Initialize directly
private:
    int maxPulses;
    int currentPulseIndexes[2];
    int nextPulseIndex;
    int activeCount;
};