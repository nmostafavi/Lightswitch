#define UNSIGNED_LONG_MAX (2^32 - 1)

const int led_pin = 13;
const int button_pin = 2;
const int speaker_pin = 8;
const int rf_receive_pin = A0;
const int rf_transmit_pin = 4;
const int bicolor_led_anode_pin = 7;
const int bicolor_led_cathode_pin = 6;
const int threshold_high = 500;  // any received value greater than this is considered HIGH
const int threshold_low = 200;  // any received value less than this is considered LOW

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT_PULLUP);
  pinMode(rf_transmit_pin, OUTPUT);
  pinMode(bicolor_led_anode_pin, OUTPUT);
  pinMode(bicolor_led_cathode_pin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(button_pin), button_press, FALLING);
}

void loop() {
}

void button_press() {
  start_recording();
}

void chirp() {
  unsigned int frequency = 2100;  // Hz
  unsigned int duration = 100;  // ms
  tone(speaker_pin, frequency, duration);
}

void led_red() {
  digitalWrite(bicolor_led_anode_pin, HIGH);
  digitalWrite(bicolor_led_cathode_pin, LOW);
}

void led_green() {
  digitalWrite(bicolor_led_anode_pin, LOW);
  digitalWrite(bicolor_led_cathode_pin, HIGH);
}

void led_off() {
  digitalWrite(bicolor_led_anode_pin, LOW);
  digitalWrite(bicolor_led_cathode_pin, LOW);
}

