/*
 LED
 Library for controlling a red/green bi-color LED.
 Created by Neema Mostafavi, November 5, 2016.
*/

#include "LED.h"

LED::LED(int bicolor_led_anode_pin, int bicolor_led_cathode_pin) {
  _bicolor_led_anode_pin = bicolor_led_anode_pin;
  _bicolor_led_cathode_pin = bicolor_led_cathode_pin;
  pinMode(_bicolor_led_anode_pin, OUTPUT);
  pinMode(_bicolor_led_cathode_pin, OUTPUT);
}

void LED::red() {
  digitalWrite(_bicolor_led_anode_pin, HIGH);
  digitalWrite(_bicolor_led_cathode_pin, LOW);
}

void LED::green() {
  digitalWrite(_bicolor_led_anode_pin, LOW);
  digitalWrite(_bicolor_led_cathode_pin, HIGH);
}

void LED::off() {
  digitalWrite(_bicolor_led_anode_pin, LOW);
  digitalWrite(_bicolor_led_cathode_pin, LOW);
}
