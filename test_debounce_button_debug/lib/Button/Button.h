/*
 Button
 Library for debouncing and detecting long-presses of a button.
 Created by Neema Mostafavi, November 5, 2016.
*/

#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"

class Button {
  public:
    Button(int button_pin);
    // Call this from within the parent loop() function. This monitors for
    // button presses and performs debouncing logic.
    void update();
    // Whether the button is being pressed down.
    bool pressed();
    // Whether the button is being held down, and has been held down for long
    // enough to be considered a "long press".
    bool long_pressed();
  private:
    // Internal function that gets called every update(). This is a separate
    // static function so that it can also be called from an interrupt, allowing
    // for better responsiveness.
    static void update_internal();
};

#endif // LED_H
