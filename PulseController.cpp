#include "PulseController.h"
#include <Arduino.h>

PulseController::PulseController(int maxPulses) : pulses(maxPulses), maxPulses(maxPulses), currentPulseIndexes{0, 0}, nextPulseIndex(0), activeCount(0)
{
}

void PulseController::createPulses()
{
  for (int i = 0; i < maxPulses; i++)
  {
    pulses[i] = Pulse();
    pulses[i].init(maxPulses, spriteLength);
  }
}

void PulseController::startPulse(int vector)
{
  nextPulseIndex++;
  currentPulseIndexes[vector] = nextPulseIndex;
  pulses[currentPulseIndexes[vector]].trigger(vector);
}

void PulseController::holdPulse(int vector)
{
  pulses[currentPulseIndexes[vector]].position = pulses[currentPulseIndexes[vector]].position + pulses[currentPulseIndexes[vector]].travelDirection;
  pulses[currentPulseIndexes[vector]].sustain();
}

void PulseController::releasePulse(int vector)
{
  pulses[currentPulseIndexes[vector]].detrigger();
}

void PulseController::updatePulses()
{
  activeCount = 0;
  for (int i = 0; i < maxPulses; i++)
  { // step through the pulse object array
    if (pulses[i].active == true)
    { // check for active pulses
      activeCount++;
      collisionDetect(i);
      int colliding = pulses[i].update();
      if (colliding != 9999)
      {
        pulses[i].expire();
      }
    }
  }
}

void PulseController::collisionDetect(int pulseIndex)
{
  if (pulses[pulseIndex].vector == 0)
  {                                           // check for this vector only
    int startA = pulses[pulseIndex].position; // get data for this pulse
    int endA = pulses[pulseIndex].end;
    for (int j = 0; j < maxPulses; j++)
    { // step through pulse object array
      if (pulses[j].active)
      { // check for active pulses only
        if (pulses[j].vector != 0)
        { // check for other vectors only
          //          Serial.println(j);
          int startB = pulses[j].position; // get data for this other pulse
          int endB = pulses[j].end;
          if (startA >= startB)
          {
            //              Serial.println("HERE");/
            if (endA - spriteLength <= endB + spriteLength)
            { // check for crossover
              Serial.println("COLLISION DETECTED");
              pulses[pulseIndex].collision = true;            // flag as this pulse colliding
              pulses[pulseIndex].colliding = pulses[j].index; // update pointer to other pulse
              pulses[j].collision = true;                     // flag as other pulse colliding
              pulses[j].colliding = pulses[pulseIndex].index; // update pointer to this pulse
            }
            else
            { // if no collision, update collision flag to false
              pulses[pulseIndex].collision = false;
              pulses[j].collision = false;
            }
          }
        }
      }
    }
    if (pulses[pulseIndex].collision == true && pulses[pulseIndex].prevCollision == false)
    { // check for collision state change rising
      Serial.println("COLLISION START");
    }
    if (pulses[pulseIndex].collision == false && pulses[pulseIndex].prevCollision == true)
    { // check for collision state change falling
      Serial.println("COLLISION END");
    }
  }
  pulses[pulseIndex].prevCollision = pulses[pulseIndex].collision; // update prevCollision flag
}