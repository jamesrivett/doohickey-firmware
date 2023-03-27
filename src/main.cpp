#include <pins.h>

#include <Arduino.h>
#include <Encoder.h>
#include <HID-Project.h>


void setup() {
  Serial.begin(9600);
  BootKeyboard.begin();
  Consumer.begin();

  pinMode(BUTTON_0, INPUT);
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  pinMode(BUTTON_3, INPUT);
  pinMode(ENC_0_BUTTON, INPUT_PULLUP);
  pinMode(ENC_1_BUTTON, INPUT_PULLUP);
  pinMode(ENC_2_BUTTON, INPUT_PULLUP);
  pinMode(ENC_3_BUTTON, INPUT_PULLUP);
}

void loop() {
  Serial.println(digitalRead(BUTTON_0));
  Serial.println(digitalRead(BUTTON_1));
  Serial.println(digitalRead(BUTTON_2));
  Serial.println(digitalRead(BUTTON_3));
  Serial.println(digitalRead(ENC_0_BUTTON));
  Serial.println(digitalRead(ENC_1_BUTTON));
  Serial.println(digitalRead(ENC_2_BUTTON));
  Serial.println(digitalRead(ENC_3_BUTTON));
  delay(50);
}