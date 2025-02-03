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

void BUTTON_0_PRESS() {
  if (SHIFT) {
    Consumer.write(HID_CONSUMER_AC_FORWARD);
  }
  else {
    Consumer.write(MEDIA_NEXT);
  }
}

void BUTTON_1_PRESS() {
  if (SHIFT) {
  }
  else {
    Consumer.write(MEDIA_PLAY_PAUSE);
  }
}

void BUTTON_2_PRESS() {
  if (SHIFT) {
    Consumer.write(HID_CONSUMER_AC_BACK);
  }
  else {
    Consumer.write(MEDIA_PREVIOUS);
  }
}

void BUTTON_ENC_0_PRESS() {
  Consumer.write(MEDIA_VOL_MUTE);
}

void BUTTON_ENC_1_PRESS() {
  BootKeyboard.write(KEY_ENTER);
}

void BUTTON_ENC_2_PRESS() {
  BootKeyboard.press(KEY_RIGHT_ALT);
  BootKeyboard.write(KEY_RIGHT_BRACE);
  BootKeyboard.release(KEY_RIGHT_ALT);
}

void BUTTON_ENC_3_PRESS() {
      if (SHIFT) {
        BootKeyboard.press(KEY_RIGHT_ALT);
        BootKeyboard.write(KEY_RIGHT_BRACE);
        BootKeyboard.release(KEY_RIGHT_ALT);
      }
      else {
        BootKeyboard.press(KEY_RIGHT_ALT);
        BootKeyboard.write(KEY_LEFT_BRACE);
        BootKeyboard.release(KEY_RIGHT_ALT);
      }
}


void ENC_0_LEFT() {
  Consumer.write(MEDIA_VOL_DOWN);
}

void ENC_0_RIGHT() {
  Consumer.write(MEDIA_VOL_UP);
}

void ENC_1_LEFT() {
  if (SHIFT) {
    SCROLLING_SPEED = constrain(SCROLLING_SPEED - 1, 1, 5);
    scrollBlink(SCROLLING_SPEED);
  }
  else {
    for (int i = 0; i < SCROLLING_SPEED; i++) {
      BootKeyboard.write(KEY_DOWN_ARROW);
    }
  }
}
void ENC_1_RIGHT() {
  if (SHIFT) {
    SCROLLING_SPEED = constrain(SCROLLING_SPEED + 1, 1, 5);
    scrollBlink(SCROLLING_SPEED);
  }
  else {
    for (int i = 0; i < SCROLLING_SPEED; i++) {
      BootKeyboard.write(KEY_UP_ARROW);
    }
  }
}

void ENC_2_LEFT() {
  BootKeyboard.write(KEY_LEFT_ARROW);
}

void ENC_2_RIGHT() {
  BootKeyboard.write(KEY_RIGHT_ARROW);
}

void ENC_3_LEFT() {
  Consumer.write(MEDIA_VOL_UP);
}
void ENC_3_RIGHT() {
  Consumer.write(MEDIA_VOL_DOWN);
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
  // Serial.println("button0: " + String(currentStates.BUTTON_0));
  // Serial.println("button1: " + String(currentStates.BUTTON_1));
  // Serial.println("button2: " + String(currentStates.BUTTON_2));
  // Serial.println("button3: " + String(currentStates.BUTTON_3));
  // Serial.println("enc_button0: " + String(currentStates.ENC_0_BUTTON));
  // Serial.println("enc_button1: " + String(currentStates.ENC_1_BUTTON));
  // Serial.println("enc_button2: " + String(currentStates.ENC_2_BUTTON));
  // Serial.println("enc_button3: " + String(currentStates.ENC_3_BUTTON));
  Serial.println("enc_0: " + String(currentStates.ENC_0));
  Serial.println("enc_1: " + String(currentStates.ENC_1));
  Serial.println("enc_2: " + String(currentStates.ENC_2));
  Serial.println("enc_3: " + String(currentStates.ENC_3));
  Serial.println("\n\n\n\n\n\n");
}