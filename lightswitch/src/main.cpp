#include <Arduino.h>
#include <RCSwitch.h>

// Set up RF receiver/transmitter
const int rf_interrupt = digitalPinToInterrupt(2);
const int rf_transmit_pin = 3;
RCSwitch rf = RCSwitch();
// Set up other
const int led_pin = 13;

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  // rf.enableReceive(rf_interrupt);
  // Serial.println("Ready to receive.");

  rf.enableTransmit(rf_transmit_pin);
  rf.setProtocol(1);
  rf.setPulseLength(190);
  Serial.println("Ready to transmit.");
}

void loop() {

  rf.send(5510451, 24);
  delay(1000);
  rf.send(5510460, 24);
  delay(1000);
  
  // if (rf.available()) {
  //   int value = rf.getReceivedValue();
  //   if (value == 0) {
  //     Serial.println("Unknown encoding.");
  //   } else {
  //     Serial.print("Received ");
  //     Serial.print(rf.getReceivedValue());
  //     Serial.print(" / ");
  //     Serial.print(rf.getReceivedBitlength());
  //     Serial.print("bit ");
  //     Serial.print(" PulseLength: ");
  //     Serial.print(rf.getReceivedDelay());
  //     Serial.print(" microseconds");
  //     Serial.print(" Protocol: ");
  //     Serial.println(rf.getReceivedProtocol());
  //   }
  //   rf.resetAvailable();
  // }
}
