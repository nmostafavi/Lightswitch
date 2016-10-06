#include <EEPROM.h>

#define UNSIGNED_LONG_MAX (2^32 - 1)

const int rf_receive_pin = A0;
const int led_pin = 13;

const int threshold_high = 500;  // any value greater than this is considered HIGH
const int threshold_low = 200;  // any value less than this is considered LOW

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  // Start recording immediately.
  bool previous_state = LOW;
  unsigned long last_state_change_time = 0;
  int count = 0;
  const unsigned int num_data_points = 128;
  unsigned long data[num_data_points];  // stores the duration of each high/low state in microseconds
  for (int i = 0; i < num_data_points; i++) {
    data[i] = 0;
  }
  digitalWrite(led_pin, LOW);
  Serial.println("Started recording.");
  while (true) {
    int val = analogRead(rf_receive_pin);
    bool current_state = previous_state;
    if (val > threshold_high) {
      current_state = HIGH;
    } else if (val < threshold_low) {
      current_state = LOW;
    }
    unsigned long current_time = micros();
    unsigned long time_since_last_state_change = current_time - last_state_change_time;
    if (current_time < last_state_change_time) {
      // The current_time value overflowed. Account for the rollover.
      time_since_last_state_change = (UNSIGNED_LONG_MAX - last_state_change_time) + current_time;
    }
    if (current_state != previous_state) {
      last_state_change_time = current_time;
      if (count < num_data_points) {
        data[count] = time_since_last_state_change;
      } else {
        Serial.println("Finished recording.");
        break;
      }
      count++;
    }
    previous_state = current_state;
  }
  digitalWrite(led_pin, HIGH);
  // Dump the received data
  Serial.print(count);
  Serial.println(" data points.");
  for (int i = 0; i < num_data_points; i++) {
    Serial.println(data[i]);
  }
}

void loop() {
}

