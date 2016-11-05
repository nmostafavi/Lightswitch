/* This program tests the debouncing of a push button. Wire up a button to Pin 2 and GND, then observe the console for high/low states of the button. */

const int led_pin = 13;
const int button_pin = 2;

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

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT_PULLUP);
}

void loop() {
  // Perform duration-threshold debouncing of button presses
  bool state = digitalRead(button_pin);
  unsigned long now = millis();
  if (state != last_unfiltered_button_state) {
    last_unfiltered_button_state_change_time = now;
    last_unfiltered_button_state = state;
  }
  if ((now - last_unfiltered_button_state_change_time) > debounce_threshold) {
    if (state != filtered_button_state) {
      filtered_button_state = state;
      last_filtered_button_state_change_time = now;
      if (state == HIGH) {
        Serial.println("HIGH"); 
      } else {
        Serial.println("LOW");
      }
    }
  }
  // Detect and respond to long button presses using the debounced button input.
  if (filtered_button_state == LOW) {
    if ((now - last_filtered_button_state_change_time) > long_press_duration) {
      Serial.println("**** LONG PRESS ****");
    }
  }
}
