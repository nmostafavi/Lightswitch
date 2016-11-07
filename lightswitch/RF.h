/*
 RF
 Library for controlling 433 MHz RF transmitter and receiver modules. Records
 received RF signals to EEPROM, which it can play back via the transmitter. 
 Capable of remembering the "on" and "off" signals of common household RF light
 switches.
 Created by Neema Mostafavi, November 5, 2016.
*/

#ifndef RF_H
#define RF_H

#include "Arduino.h"

class RF {
  public:
    RF(int rf_receive_pin, int rf_transmit_pin);
    // Records 128 data points and stores them in EEPROM. This is a blocking call.
    void record(bool on);
    // Replays an RF signal stored in EEPROM. This is a blocking call.
    void playback(bool on);
  private:
    int _rf_receive_pin;
    int _rf_transmit_pin;
};

#endif // RF_H
