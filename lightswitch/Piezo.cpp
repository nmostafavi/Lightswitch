/*
  Piezo
  Library for playing back simple confirmation sounds on a piezo.
  Created by Neema Mostafavi, November 5, 2016.
*/

#include "Piezo.h"

Piezo::Piezo(int speaker_pin) {
  _pin = speaker_pin;
}

void Piezo::tone_mid() {
  tone(_pin, 1200, 100);
  delay(100);
  tone(_pin, 1200, 100);
}

void Piezo::tone_up() {
  tone(_pin, 600, 100);
  delay(100);
  tone(_pin, 800, 100);
}

void Piezo::tone_down() {
  tone(_pin, 800, 100);
  delay(100);
  tone(_pin, 600, 100);
}
