/* This program tests the debouncing of a push button. Wire up a button to Pin 2 and GND, then observe the console for high/low states of the button. */

const int led_pin = 13;
const int button_pin = 2;

// The debounced button state. For an INPUT_PULLUP pin, the default state is HIGH.
bool button_state = HIGH;
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
  bool state = digitalRead(button_pin);
  unsigned long now = millis();
  if (state != last_unfiltered_button_state) {
    last_unfiltered_button_state_change_time = now;
    last_unfiltered_button_state = state;
  }
  if ((now - last_unfiltered_button_state_change_time) > debounce_threshold) {
    if (state != button_state) {
      button_state = state;
      if (state == HIGH) {
        Serial.println("HIGH"); 
      } else {
        Serial.println("LOW");
      }
    }
  }
}
