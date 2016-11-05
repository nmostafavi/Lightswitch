/*
 RF
 Library for controlling 433 MHz RF transmitter and receiver modules. Records
 received RF signals to EEPROM, which it can play back via the transmitter.
 Capable of remembering the "on" and "off" signals of common household RF light
 switches. 
 Created by Neema Mostafavi, November 5, 2016.
*/

#include "RF.h"
#include <EEPROM.h>

#define UNSIGNED_LONG_MAX (2^32 - 1)

const int threshold_high = 500;  // any received value greater than this is considered HIGH
const int threshold_low = 200;  // any received value less than this is considered LOW
const unsigned int num_data_points = 128;  // number of data points stored in EEPROM for each recorded remote control signal

RF::RF(int rf_receive_pin, int rf_transmit_pin) {
  _rf_receive_pin = rf_receive_pin;
  _rf_transmit_pin = rf_transmit_pin;
  pinMode(rf_transmit_pin, OUTPUT);
}

void RF::record(bool on) {
  bool previous_state = LOW;
  unsigned long last_state_change_time = 0;
  int count = 0;
  unsigned long data[num_data_points];  // stores the duration of each high/low state in microseconds
  for (int i = 0; i < num_data_points; i++) {
    data[i] = 0;
  }
//  digitalWrite(led_pin, HIGH);
//  Serial.println("Started recording.");
  while (true) {
    int val = analogRead(_rf_receive_pin);
    bool current_state = previous_state;
    if (val > threshold_high) {
      current_state = HIGH;
    } else if (val < threshold_low) {
      current_state = LOW;
    }
    if (current_state != previous_state) {
      unsigned long current_time = micros();
      unsigned long time_since_last_state_change = current_time - last_state_change_time;
      if (current_time < last_state_change_time) {
        // The current_time value overflowed. Account for the rollover.
        time_since_last_state_change = (UNSIGNED_LONG_MAX - last_state_change_time) + current_time;
      }
      if (count < num_data_points) {
        data[count] = time_since_last_state_change;
      } else {
//        Serial.println("Finished recording.");
        break;
      }
      last_state_change_time = current_time;
      previous_state = current_state;
      count++;
    }
  }
//  digitalWrite(led_pin, LOW);
//  // Dump the received data
//  Serial.print("Captured ");
//  Serial.print(count);
//  Serial.println(" data points.");
  for (int i = 0; i < num_data_points; i++) {
//    Serial.print(i);
//    Serial.print("\t");
//    Serial.println(data[i]);
    int address = i * sizeof(unsigned long);
    if (on == true) {
      address += num_data_points * sizeof(unsigned long);
    }
    EEPROM.put(address, data[i]);
  }
}

void RF::playback(bool on) {
//  Serial.println("Playing back...");
  for (int i = 0; i < num_data_points; i++) {
    bool state = i % 2;
    int address = i * sizeof(unsigned long);
    if (on == true) {
      address += num_data_points * sizeof(unsigned long);
    }
    unsigned long value = 0;
    EEPROM.get(address, value);
    digitalWrite(_rf_transmit_pin, state);
    delayMicroseconds(value);
  }
  digitalWrite(_rf_transmit_pin, LOW);
//  Serial.println("Finished.");
}
