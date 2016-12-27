#include <Arduino.h>
#include <EEPROM.h>
#include <Piezo.h>
#include <LED.h>
#include <Button.h>
#include <RCSwitch.h>

// Set up piezo speaker
const int speaker_pin = 8;
Piezo piezo(speaker_pin);
// Set up LEDs
const int bicolor_led_anode_pin = 7;
const int bicolor_led_cathode_pin = 6;
LED led(bicolor_led_anode_pin, bicolor_led_cathode_pin);
// Set up RF receiver/transmitter
const int rf_interrupt = digitalPinToInterrupt(3);
const int rf_transmit_pin = 4;
RCSwitch rf = RCSwitch();
// Set up button
const int button_pin = 2;
Button button(button_pin);
// Set up other
const int led_pin = 13;

bool is_recording = false;
bool is_recording_on_signal = false;
bool did_record_on_signal = false;
bool is_recording_off_signal = false;
bool did_record_off_signal = false;

unsigned long on_signal = 0;
unsigned long off_signal = 0;

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  rf.enableTransmit(rf_transmit_pin);
  rf.setProtocol(1);
  rf.setPulseLength(190);
  Serial.println("Ready.");
}

void loop() {
  button.update();
  if (is_recording == false) {
    if (button.long_pressed()) {
      for (int i = 0; i < 4; i++) {
        led.red();
        delay(100);
        led.off();
        delay(100);
      }
      led.red();
      piezo.tone_down();
      rf.enableReceive(rf_interrupt);
      is_recording = true;
      is_recording_on_signal = true;
      did_record_on_signal = false;
      is_recording_off_signal = false;
      did_record_off_signal = false;
    } else if (button.pressed()) {
      // Send a test on/off signal
      rf.send(on_signal, 24);
      for (int i = 0; i < 6; i++) {
        led.green();
        delay(100);
        led.off();
        delay(100);
      }
      rf.send(off_signal, 24);
    } else {
      // Monitoring mode: Watch for changes to the input pin, then transmit the
      // corresponding RF signal.
    }
  }
  if (is_recording == true) {
    if (button.pressed() == true &&
       did_record_on_signal == true &&
       is_recording_off_signal == false) {
      is_recording_off_signal = true;
    }
    if (rf.available()) {
      unsigned long value = rf.getReceivedValue();
      unsigned int bit_length = rf.getReceivedBitlength();
      unsigned int pulse_length = rf.getReceivedDelay();
      unsigned int protocol = rf.getReceivedProtocol();
      if (value != 0 && bit_length == 24 && pulse_length == 190 && protocol == 1) {
        if (is_recording_on_signal == true) {
          Serial.print("Received 'on' signal: ");
          Serial.println(value);
          on_signal = value;//Save to EEPROM
          piezo.tone_mid();
          for (int i = 0; i < 4; i++) {
            led.off();
            delay(100);
            led.red();
            delay(100);
          }
          is_recording_on_signal = false;
          did_record_on_signal = true;
        }
        if (is_recording_off_signal == true) {
          Serial.print("Received 'off' signal: ");
          Serial.println(value);
          off_signal = value;//Save to EEPROM
          piezo.tone_up();
          for (int i = 0; i < 4; i++) {
            led.off();
            delay(100);
            led.green();
            delay(100);
          }
          led.off();
          is_recording_off_signal = true;
          did_record_off_signal = true;
          is_recording = false;
          rf.disableReceive();
        }
      }
      rf.resetAvailable();
    }
  }
}
