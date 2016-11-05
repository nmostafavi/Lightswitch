#include "Piezo.h"
#include "LED.h"
#include "RF.h"
#include "Button.h"

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
// Set up button
const int button_pin = 2;
Button button(button_pin);
// Set up other
const int led_pin = 13;

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
}

void loop() {
  button.update();
  bool state = button.state();
  digitalWrite(led_pin, state);
  if (button.long_pressed()) {
    Serial.println("**** LONG PRESS ****");
  }
}

