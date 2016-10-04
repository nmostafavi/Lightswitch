/* This program will transmit a periodic 433 MHz signal for testing */

const int rf_transmit_pin = 4;
const int led_pin = 13;

void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(rf_transmit_pin, OUTPUT);
}

void loop() {
  digitalWrite(rf_transmit_pin, HIGH);
  digitalWrite(led_pin, HIGH);
  delay(100);
  digitalWrite(rf_transmit_pin, LOW);
  digitalWrite(led_pin, LOW);
  delay(100);
  digitalWrite(rf_transmit_pin, HIGH);
  digitalWrite(led_pin, HIGH);
  delay(100);
  digitalWrite(rf_transmit_pin, LOW);
  digitalWrite(led_pin, LOW);
  delay(500);
}

