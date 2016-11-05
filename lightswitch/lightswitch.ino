#include "Piezo.h"
#include "LED.h"
#include "RF.h"

// Set up piezo speaker
const int speaker_pin = 8;
Piezo piezo(speaker_pin);
// Set up LEDs
const int bicolor_led_anode_pin = 7;
const int bicolor_led_cathode_pin = 6;
LED led(bicolor_led_anode_pin, bicolor_led_cathode_pin);
// Set up RF receiver/transmitter and recording to EEPROM
const int rf_receive_pin = A0;
const int rf_transmit_pin = 4;
RF rf(rf_receive_pin, rf_transmit_pin);
// Set up other
const int led_pin = 13;
const int button_pin = 2;
volatile bool button_pressed = false;

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(button_pin), button_press, FALLING);
}

void loop() {
  if (button_pressed == true) {
    button_pressed = false;
  }
}

void button_press() {
  button_pressed = true;
}

