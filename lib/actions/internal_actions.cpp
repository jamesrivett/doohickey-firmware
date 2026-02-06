#include <Arduino.h>
#include <HID-Project.h>
#include <Encoder.h>

#include "inputs.hpp"
#include "actions.h"
#include "state.h"

void doohickeyInit() {
  Serial.begin(9600);
  BootKeyboard.begin();
  Consumer.begin();

  pinMode(BUTTON_0, INPUT_PULLUP);
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(ENC_0_BUTTON, INPUT_PULLUP);
  pinMode(ENC_1_BUTTON, INPUT_PULLUP);
  pinMode(ENC_2_BUTTON, INPUT_PULLUP);
  pinMode(ENC_3_BUTTON, INPUT_PULLUP);
}

void scrollBlink(int scrolling_speed) {
  for (int i = 0; i < 3; i++) {
    delay(200 / scrolling_speed);
    TXLED1;
    delay(200 / scrolling_speed);
    TXLED0;
  }
}

void doohickeyDebug() {
  Serial.println("button0: " + String(currentStates.BUTTON_0));
  Serial.println("button1: " + String(currentStates.BUTTON_1));
  Serial.println("button2: " + String(currentStates.BUTTON_2));
  Serial.println("button3: " + String(currentStates.BUTTON_3));
  Serial.println("enc_button0: " + String(currentStates.ENC_0_BUTTON));
  Serial.println("enc_button1: " + String(currentStates.ENC_1_BUTTON));
  Serial.println("enc_button2: " + String(currentStates.ENC_2_BUTTON));
  Serial.println("enc_button3: " + String(currentStates.ENC_3_BUTTON));
  Serial.println("enc_0: " + String(currentStates.ENC_0));
  Serial.println("enc_1: " + String(currentStates.ENC_1));
  Serial.println("enc_2: " + String(currentStates.ENC_2));
  Serial.println("enc_3: " + String(currentStates.ENC_3));
  Serial.println("\n\n\n\n\n\n");
}