/* This program will blink the LED high/low when a 433 MHz signal is received. */

const int rf_receive_pin = A0;
const int led_pin = 13;

const int threshold_high = 500;  // any value greater than this is considered HIGH
const int threshold_low = 200;  // any value less than this is considered LOW

bool previous_state = LOW;
float moving_average = 0;

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
}

void loop() {
  // Read the data value from the RF receiver
  int val = analogRead(rf_receive_pin);
  // Use thresholding to determine whether the value is HIGH or LOW,
  // ignoring values that fall inbetween the upper and lower threshold.
  bool current_state = previous_state;
  if (val > threshold_high) {
    current_state = HIGH;
  }
  if (val < threshold_low) {
    current_state = LOW;
  }
  Serial.println(current_state);
  if (current_state != previous_state) {
    digitalWrite(led_pin, current_state);
    // Update current values for next loop iteration
    previous_state = current_state;
  }
  delay(1);
}

