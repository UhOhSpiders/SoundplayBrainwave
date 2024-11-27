#include <Arduino.h>
#include "MidiController.h"

MidiController::MidiController(int channel1, int channel2) : channels{channel1, channel2}
{
    init();
}

void MidiController::startNote(int channelIndex)
{
    usbMIDI.sendNoteOn(50, 100, channels[channelIndex]);
    Serial.println("start note");
}

void MidiController::stopNote(int channelIndex)
{
    usbMIDI.sendNoteOff(50, 100, channels[channelIndex]);
    Serial.println("stop note");
}

void MidiController::init()
{
    // usbMIDI.begin();
}