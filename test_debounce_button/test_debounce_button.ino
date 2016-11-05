/* This program tests the debouncing of a push button. */

const int led_pin = 13;
const int button_pin = 2;

// The debounced button state.
bool button_state = HIGH;
// The unfiltered last state of the button.
bool last_button_state = HIGH;
unsigned long last_button_state_change_time = 0;
unsigned long debounce_threshold = 50;

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT_PULLUP);
}

void loop() {
  bool state = digitalRead(button_pin);
  unsigned long now = millis();
  if (state != last_button_state) {
    last_button_state_change_time = now;
    last_button_state = state;
  }
  if ((now - last_button_state_change_time) > debounce_threshold) {
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
