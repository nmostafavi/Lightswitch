/*
  Piezo
  Library for playing back simple confirmation sounds on a piezo.
  Created by Neema Mostafavi, November 5, 2016.
*/

#ifndef PIEZO_H
#define PIEZO_H

#include "Arduino.h"

class Piezo {
  public:
    Piezo(int speaker_pin);
    // Plays a flat beep
    void tone_mid();
    // Plays an upward beep
    void tone_up();
    // Plays a downward beep
    void tone_down();
  private:
    int _pin;
};

#endif // PIEZO_H
