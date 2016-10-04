/* This program tests a push button. An LED is illuminated when 
  a push button is pressed. The switch must be connected to 
  ground on one end, and pin 2 on the other. */

const int led_pin = 13;
const int button_pin = 2;
volatile bool state = LOW;

void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(button_pin), foo, CHANGE);
}

void loop() {
  digitalWrite(led_pin, state);
  delay(1);
}

void foo() {
  state = !digitalRead(button_pin);
}

