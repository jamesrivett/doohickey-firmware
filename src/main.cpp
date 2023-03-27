
#include <Arduino.h>
#include <Encoder.h>
#include <HID-Project.h>



void setup() {
  Serial.begin(9600);
  BootKeyboard.begin();
  Consumer.begin();
}

void loop() {

}