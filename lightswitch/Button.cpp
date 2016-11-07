/*
 Button
 Library for debouncing and detecting long-presses of a button.
 Created by Neema Mostafavi, November 5, 2016.
*/

#include "Button.h"

// The filtered (i.e. debounced) button state. For an INPUT_PULLUP pin, the default state is HIGH.
bool filtered_button_state = HIGH;
// The last time the filtered (i.e. debounced) button state has changed.
unsigned long last_filtered_button_state_change_time = 0;
// How many milliseconds the button has to be held down to register as a "long press". This can be used to initiate a special mode in the program.
unsigned long long_press_duration = 1200;

// The unfiltered last state of the button.
bool last_unfiltered_button_state = HIGH;
// The last time the button's unfiltered state has changed.
unsigned long last_unfiltered_button_state_change_time = 0;
// The number of milliseconds that the button should be consistently in its HIGH or LOW state to register as a button press or button release.
unsigned long debounce_threshold = 50;

Button::Button(int button_pin) {
  _button_pin = button_pin;
  pinMode(_button_pin, INPUT_PULLUP);
}

bool Button::pressed() {
  if (filtered_button_state == LOW) {
    return true;
  } else {
    return false;
  }
}

bool Button::long_pressed() {
  if (filtered_button_state == LOW) {
    unsigned long now = millis();
    if ((now - last_filtered_button_state_change_time) > long_press_duration) {
      return true;
    }
  }
  return false;
}

void Button::update() {
  // Perform duration-threshold debouncing of button presses
  bool state = digitalRead(_button_pin);
  unsigned long now = millis();
  if (state != last_unfiltered_button_state) {
    last_unfiltered_button_state_change_time = now;
    last_unfiltered_button_state = state;
  }
  if ((now - last_unfiltered_button_state_change_time) > debounce_threshold) {
    if (state != filtered_button_state) {
      filtered_button_state = state;
      last_filtered_button_state_change_time = now;
    }
  }
}
