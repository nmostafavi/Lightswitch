/*
 LED
 Library for controlling a red/green bi-color LED.
 Created by Neema Mostafavi, November 5, 2016.
*/

#ifndef LED_H
#define LED_H

#include "Arduino.h"

class LED {
  public:
    LED(int bicolor_led_anode_pin, int bicolor_led_cathode_pin);
    // Turns the bi-color LED red
    void red();
    // Turns the bi-color LED green
    void green();
    // Turns the bi-color LED off
    void off();
  private:
    int _bicolor_led_anode_pin;
    int _bicolor_led_cathode_pin;
};

#endif // LED_H
