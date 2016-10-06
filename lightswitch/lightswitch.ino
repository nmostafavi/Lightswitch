const int led_pin = 13;
const int button_pin = 2;
const int speaker_pin = 8;
const int rf_receive_pin = A0;
const int rf_transmit_pin = 4;
volatile bool button_state = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT_PULLUP);
  pinMode(rf_transmit_pin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(button_pin), button_press, CHANGE);
}

void loop() {
}

void button_press() {
  bool button_state = !digitalRead(button_pin);
  if (button_state == HIGH) {
    chirp();
  }
}

void chirp() {
  unsigned int frequency = 31;  //2100;  // Hz
  unsigned int duration = 100;  // ms
  unsigned int pause = 10;  // ms
  tone(speaker_pin, frequency, duration);
  delay(duration + pause);
  tone(speaker_pin, frequency, duration);
}

