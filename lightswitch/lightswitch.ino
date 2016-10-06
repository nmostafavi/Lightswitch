const int led_pin = 13;
const int button_pin = 2;
const int speaker_pin = 8;
const int rf_receive_pin = A0;
const int rf_transmit_pin = 4;

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT_PULLUP);
  pinMode(rf_transmit_pin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(button_pin), button_press, FALLING);
}

void loop() {
}

void button_press() {
  // can attempt to de-bounce button input here, if needed.
  chirp();
}

void chirp() {
  unsigned int frequency = 31;  //2100;  // Hz
  unsigned int duration = 100;  // ms
  unsigned int pause = 10;  // ms
  digitalWrite(led_pin, HIGH);
  tone(speaker_pin, frequency, duration);
  delay(duration + pause);
  tone(speaker_pin, frequency, duration);
  digitalWrite(led_pin, LOW);
}

