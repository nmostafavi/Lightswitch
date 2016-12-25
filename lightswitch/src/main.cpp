#include <Arduino.h>
#include <RCSwitch.h>

// Set up RF receiver/transmitter
const int rf_interrupt_pin = 0;
const int rf_transmit_pin = 4;
RCSwitch rf = RCSwitch();
// Set up other
const int led_pin = 13;

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  rf.enableReceive(rf_interrupt_pin);
  Serial.println("Ready.");
}

void loop() {
  if (rf.available()) {
    int value = rf.getReceivedValue();
    if (value == 0) {
      Serial.println("Unknown encoding.");
    } else {
      Serial.print("Received ");
      Serial.print(rf.getReceivedValue());
      Serial.print(" / ");
      Serial.print(rf.getReceivedBitlength());
      Serial.print("bit ");
      Serial.print("Protocol: ");
      Serial.println(rf.getReceivedProtocol());
    }
    rf.resetAvailable();
  }
}
