#pragma once
#include <array>
// #include <MIDI.h>

class MidiController
{
public:
    MidiController(int channel1, int channel2);
    std::array<int, 2> channels;
    void startNote(int channelIndex);
    void stopNote(int channelIndex);
    void init();
};