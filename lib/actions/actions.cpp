#include <Arduino.h>
#include <HID-Project.h>
#include <Encoder.h>

#include "inputs.h"
#include "actions.h"
#include "state.h"

void doohickeyInit() {
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
  switch (modeState) {
    case normal:
      Consumer.write(MEDIA_VOL_MUTE);
      break;
    case lefty:
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
      break;
    default:
      break;
  }
}

void BUTTON_ENC_1_PRESS() {
  switch (modeState) {
    case normal:
      BootKeyboard.write(KEY_ENTER);
      break;
    default:
      break;
  }
}

void BUTTON_ENC_2_PRESS() {
  switch (modeState) {
    case lefty:
      BootKeyboard.write(KEY_ENTER);
      break;
    default:
      break;
  }
}

void BUTTON_ENC_3_PRESS() {
  switch (modeState) {
    case normal:
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
      break;
    case lefty:
      Consumer.write(MEDIA_VOL_MUTE);
      break;
    case photoshop:
      BootKeyboard.press(KEY_SPACE);
      break;
    default:
      break;
  }
}

void BUTTON_ENC_3_RELEASE() {
  switch (modeState) {
    case photoshop:
      BootKeyboard.release(KEY_SPACE);
    default:
      break;
  }
}

void ENC_0_LEFT() {
  switch (modeState) {
    case normal:
      Consumer.write(MEDIA_VOL_DOWN);
      break;
    case photoshop:
      BootKeyboard.write(KEY_LEFT_BRACE);
      break;
    default:
      break;
  }
}
void ENC_0_RIGHT() {
  switch (modeState) {
    case normal:
      Consumer.write(MEDIA_VOL_UP);
      break;
    case photoshop:
      BootKeyboard.write(KEY_RIGHT_BRACE);
      break;
    default:
      break;
  }
}

void ENC_1_LEFT() {
  switch (modeState) {
    case normal:
      if (SHIFT) {
        SCROLLING_SPEED = constrain(SCROLLING_SPEED - 1, 1, 5);
        scrollBlink(SCROLLING_SPEED);
      }
      else {
        for (int i = 0; i < SCROLLING_SPEED; i++) {
          BootKeyboard.write(KEY_DOWN_ARROW);
        }
      }
      break;
    case lefty:
      BootKeyboard.write(KEY_LEFT_ARROW);
      break;
    default:
      break;
  }
}
void ENC_1_RIGHT() {
  switch (modeState) {
    case normal:
      if (SHIFT) {
        SCROLLING_SPEED = constrain(SCROLLING_SPEED + 1, 1, 5);
        scrollBlink(SCROLLING_SPEED);
      }
      else {
        for (int i = 0; i < SCROLLING_SPEED; i++) {
          BootKeyboard.write(KEY_UP_ARROW);
        }
      }
      break;
    case lefty:
      BootKeyboard.write(KEY_RIGHT_ARROW);
      break;
    default:
      break;
  }
}

void ENC_2_LEFT() {
  switch (modeState) {
    case normal:
      BootKeyboard.write(KEY_LEFT_ARROW);
      break;
    case lefty:
      if (SHIFT) {
        SCROLLING_SPEED = constrain(SCROLLING_SPEED - 1, 1, 5);
        scrollBlink(SCROLLING_SPEED);
      }
      else {
        for (int i = 0; i < SCROLLING_SPEED; i++) {
          BootKeyboard.write(KEY_DOWN_ARROW);
        }
      }
      break;
    default:
      break;
  }
}
void ENC_2_RIGHT() {
  switch (modeState) {
    case normal:
      BootKeyboard.write(KEY_RIGHT_ARROW);
      break;
    case lefty:
      if (SHIFT) {
        SCROLLING_SPEED = constrain(SCROLLING_SPEED + 1, 1, 5);
        scrollBlink(SCROLLING_SPEED);
      }
      else {
        for (int i = 0; i < SCROLLING_SPEED; i++) {
          BootKeyboard.write(KEY_UP_ARROW);
        }
      }
      break;
    default:
      break;
  }
}

void ENC_3_LEFT() {
  switch (modeState) {
    case lefty:
      Consumer.write(MEDIA_VOL_DOWN);
      break;
    case photoshop:
      if(SHIFT) {
        BootKeyboard.press(KEY_LEFT_CTRL);
        BootKeyboard.write(KEY_Z);
        BootKeyboard.release(KEY_LEFT_CTRL);
      }
      else {
        BootKeyboard.press(KEY_LEFT_CTRL);
        BootKeyboard.write(HID_KEYBOARD_MINUS_AND_UNDERSCORE);
        BootKeyboard.releaseAll();
      }
      break;
    default:
      break;
  }
}
void ENC_3_RIGHT() {
  switch (modeState) {
    case lefty:
      Consumer.write(MEDIA_VOL_UP);
      break;
    case photoshop:
      if(SHIFT) {
        BootKeyboard.press(KEY_LEFT_CTRL);
        BootKeyboard.press(KEY_LEFT_SHIFT);
        BootKeyboard.write(KEY_Z);
        BootKeyboard.release(KEY_LEFT_SHIFT);
        BootKeyboard.release(KEY_LEFT_CTRL);
      }
      else {
        BootKeyboard.press(KEY_LEFT_CTRL);
        BootKeyboard.write(HID_KEYBOARD_EQUALS_AND_PLUS);
        BootKeyboard.releaseAll();
      }
      break;
    default:
      break;
  }
}

void modeBlink(int mode) {
  TXLED1;
  delay(50);
  TXLED0;
  delay(50);
  TXLED1;
  delay(50);
  TXLED0;
  delay(50);

  for (u8 i = 0; i < (mode + 1); i++) {
    TXLED1;
    delay(300);
    TXLED0;
    delay(300);
  }
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
}