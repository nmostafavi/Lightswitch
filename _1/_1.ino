#include <EEPROM.h>

#define UNSIGNED_LONG_MAX (2^32 - 1)

const int rf_receive_pin = A0;
const int led_pin = 13;

const int threshold_high = 500;  // any value greater than this is considered HIGH
const int threshold_low = 200;  // any value less than this is considered LOW

bool previous_state = LOW;
unsigned long last_state_change_time = 0;  // time in microseconds
int count = 0;
const unsigned int num_data_points = 128;
unsigned long data[num_data_points];  // stores the duration of each high/low state in microseconds

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  for (int i = 0; i < num_data_points; i++) {
    data[i] = 0;
  }
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
  // Whenever the state changes, record how long the signal was in its previous state.
  if (current_state != previous_state) {
    unsigned long current_time = micros();
    unsigned long time_since_last_state_change = current_time - last_state_change_time;
    if (current_time < last_state_change_time) {
      // The current_time value overflowed. Account for the rollover.
      time_since_last_state_change = (UNSIGNED_LONG_MAX - last_state_change_time) + current_time;
    }
    if (count == num_data_points) {
      // Aggregate and print data in batches, since serial rx/tx produces RF interference
      // that messes with the logged numbers.
      for (int i = 0; i < num_data_points; i++) {
        if (i%2 == 0) {
          Serial.print("high, ");
        } else {
          Serial.print("low,  ");
        }
        Serial.println(data[i]);
      }
      count = 0;
    }
    if (count < num_data_points) {
      data[count] = time_since_last_state_change;
    }
    // Update current values for next loop iteration
    previous_state = current_state;
    last_state_change_time = current_time;
    count++;
  }
  delay(1);
}

