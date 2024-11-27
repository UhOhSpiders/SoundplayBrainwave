#include "pulse.h"

int numPixels = 0;
int spriteLength = 0;

Pulse::Pulse() {
  //  init();
}

void Pulse::init(int nP, int sL) {
  numPixels = nP;
  spriteLength = sL;
  active = false;
  vector = 0;
  position = 0;
  hold = 0;
  end = 0;
  seed = 0;
  velocity = 0;
  collision = false;
  prevCollision = false;
  colliding = 0;
}

void Pulse::trigger(int vct) {
  vector = vct;
  if (vector == 0) {
    position = 0;
    hold = 1;
    end = numPixels - hold;
  }
  if (vector == 1) {
    position = numPixels;
    hold = 1;
    end = numPixels + hold;
  }
  active = true;
  seed = random(0, 6);  // generate seed
}

void Pulse::sustain() {
  hold++;
  if (vector == 0) {
    end = position - hold;
  }
  if (vector == 1) {
    end = position + hold;
  }
}


void Pulse::detrigger() {
  if (vector == 0) {
    hold = position;
    end = position - hold;
  }
  if (vector == 1) {
    hold = numPixels - position;
    end = position + hold;
  }
}


int Pulse::update() {
  //  Serial.println(spriteLength);
  //  int noteOffIndexA;
  int noteOffIndexB = 9999;
  //  struct ab ab_instance;
  if (vector == 0) {
    position++;
    end++;
    if (position >= numPixels  + spriteLength + 1) {
      position--;
      hold--;
    }
    if (hold <= 0) {
      noteOffIndexB = 8888;
      if (collision) {
        //        noteOffIndexA = index;
        noteOffIndexB = colliding;
      }
      //      expire();
    }
  }

  if (vector == 1) {
    position--;
    end--;
    if (position <= 0  - spriteLength - 1) {
      position++;
      hold--;
    }
    if (hold <= 0) {
      noteOffIndexB = 8888;
      if (collision) {
        //        noteOffIndexA = index;
        noteOffIndexB = colliding;
      }
      //      expire();
    }
  }

  return noteOffIndexB;
}

bool Pulse::crossoverZone(int offset, Pulse colliding) {
  if (vector == 0) {
    if (position - offset >= colliding.position) {
      if (position - offset <= colliding.end) {
        return true;
      }
      else return false;
    }
    else return false;
  }
  if (vector == 1) {
    if (position - offset <= colliding.position) {
      if (position - offset >= colliding.end) {
        return true;
      }
      else return false;
    }
    else return false;
  }
}

void Pulse::expire() {
  active = false;
  vector = 0;
  position = 0;
  hold = 0;
  end = 0;
  seed = 0;
  velocity = 0;
  collision = false;
  prevCollision = false;
  colliding = 0;
}
