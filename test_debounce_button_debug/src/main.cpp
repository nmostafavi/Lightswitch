/* Testing and debugging of the Button library */
#include <Arduino.h>
#include <Button.h>

// Set up button
const int button_pin = 2;
Button button(button_pin);
// Set up other
const int led_pin = 13;

bool is_recording = false;

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  Serial.println("Ready!");
  digitalWrite(led_pin, LOW);
}

void loop() {
  button.update();
  if (button.long_pressed() && is_recording == false) {
    Serial.println("Beginning first step... *********************************");
    digitalWrite(led_pin, HIGH);
    delay(1500);
    Serial.println("First step done. Awaiting next button press. ************");
    is_recording = true;
  } else if (button.pressed() && is_recording == true) {
    Serial.println("Beginning second step... ********************************");
    delay(1500);
    digitalWrite(led_pin, LOW);
    Serial.println("Finished! ***********************************************");
    is_recording = false;
  }
}
