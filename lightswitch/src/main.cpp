#include <Arduino.h>
#include <EEPROM.h>
#include <Piezo.h>
#include <LED.h>
#include <RF.h>
#include <Button.h>

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

bool is_recording = false;

void setup() {
  // Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  Serial.println("Ready.");
}

void loop() {
  button.update();
  if (button.long_pressed()) {
    Serial.println("Beginning recording of the \"on\" signal.");
    // Beep and set LED to red
    piezo.tone_down();
    led.red();
    // Begin recording the "on" signal.
    rf.record(true);
    // When finished, confirm with a flat beep.
    piezo.tone_mid();
    // Wait until next button press.
    Serial.println("Finished recording \"on\" signal. Waiting for button press before recording the \"off\" signal.");
    is_recording = true;
  } else if (button.pressed() && is_recording == true) {
    // Begin recording the "off" signal
    rf.record(false);
    // When finished, confirm with an ascending beep and set the LED to green.
    piezo.tone_up();
    led.green();
    Serial.println("Finished recording the \"off\" signal.");
    Serial.println("Ready.");
    is_recording = false;
  } else if (button.pressed() && is_recording == false) {
    // Send a test on/off signal
    rf.playback(true);
    delay(1000);
    rf.playback(false);
    led.off();
  } else {
    // Monitoring mode: Watch for changes to the input pin, then transmit the
    // corresponding RF signal.

  }
}
