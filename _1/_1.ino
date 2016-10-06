#include <EEPROM.h>

#define UNSIGNED_LONG_MAX (2^32 - 1)

const int rf_receive_pin = A0;
const int led_pin = 13;

const int threshold_high = 500;  // any value greater than this is considered HIGH
const int threshold_low = 200;  // any value less than this is considered LOW

unsigned long idle_threshold = 20000;

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  // Start recording
  bool previous_state = LOW;
  unsigned long last_state_change_time = 0;
  int count = 0;
  const unsigned int num_data_points = 128;
  unsigned long data[num_data_points];  // stores the duration of each high/low state in microseconds
  for (int i = 0; i < num_data_points; i++) {
    data[i] = 0;
  }
  bool started_recording = false;
  while (true) {
    int val = analogRead(rf_receive_pin);
    bool current_state = previous_state;
    if (val > threshold_high) {
      current_state = HIGH;
    } else if (val < threshold_low) {
      current_state = LOW;
    }
    if (started_recording == false && previous_state == HIGH && current_state == LOW) {
      // Start recording data, starting with the duration of the first HIGH state
      started_recording = true;
      Serial.println("Started recording.");
    }
    if (started_recording == true) {
      unsigned long current_time = micros();
      unsigned long time_since_last_state_change = current_time - last_state_change_time;
      if (current_time < last_state_change_time) {
        // The current_time value overflowed. Account for the rollover.
        time_since_last_state_change = (UNSIGNED_LONG_MAX - last_state_change_time) + current_time;
      }
      if (current_state == LOW && time_since_last_state_change > idle_threshold) {
        // Received LOW state for longer than the specified threshold.
        // No new data appears to be streaming in.
        Serial.println("Detected idle state.");
        break;
      }
      if (current_state != previous_state) {
        if (count < num_data_points) {
          data[count] = time_since_last_state_change;
        } else {
          // Recording memory is full.
          Serial.println("Ran out of storage space.");
          break;
        }
        last_state_change_time = current_time;
        count++;
      }
    }
    previous_state = current_state;
  }
  digitalWrite(led_pin, HIGH);
  // Dump the received data
  for (int i=0; i<=count; i++) {
    Serial.println(data[i]);
  }
}

void loop() {
}

