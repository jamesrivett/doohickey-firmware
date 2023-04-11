#include <Arduino.h>
#include <HID-Project.h>
#include <Encoder.h>

#include "inputs.hpp"
#include "actions.hpp"
#include "state.hpp"


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
    switch(MODE) {
        case 0:
        Consumer.write(MEDIA_VOL_MUTE);
        break;
        case 1:
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
    }
}

void BUTTON_ENC_1_PRESS() {
    switch(MODE) {
      case 0:
        BootKeyboard.write(KEY_ENTER);
        break;
    }
}

void BUTTON_ENC_2_PRESS() {
    switch(MODE) {
      case 1:
        BootKeyboard.write(KEY_ENTER);
        break;
    }
}

void BUTTON_ENC_3_PRESS() {
    switch(MODE) {
      case 0:
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
      case 1:
        Consumer.write(MEDIA_VOL_MUTE);
        break;
      case 2:
        BootKeyboard.press(KEY_SPACE);
        break;
    }
}

void BUTTON_ENC_3_RELEASE() {
    switch(MODE) {
      case 2:
        BootKeyboard.release(KEY_SPACE);
    }
}

void ENC_0_LEFT() {
    switch(MODE) {
      case 0:
        Consumer.write(MEDIA_VOL_DOWN);
        break;
      case 2:
        BootKeyboard.write(KEY_LEFT_BRACE);
        break;
    }
}
void ENC_0_RIGHT() {
    switch(MODE) {
      case 0:
        Consumer.write(MEDIA_VOL_UP);
        break;
      case 2:
        BootKeyboard.write(KEY_RIGHT_BRACE);
        break;
    }
}

void ENC_1_LEFT() {
    switch(MODE) {
      case 0:
        if (SHIFT) {
          SCROLLING_SPEED = constrain(SCROLLING_SPEED-1, 1, 5);
          scrollBlink(SCROLLING_SPEED);
        }
        else {
          for (int i = 0; i < SCROLLING_SPEED; i++) {
            BootKeyboard.write(KEY_DOWN_ARROW);
          }
        }
        break;
      case 1:
        BootKeyboard.write(KEY_LEFT_ARROW);
        break;
    }
}
void ENC_1_RIGHT() {
    switch(MODE) {
      case 0:
        if (SHIFT) {
          SCROLLING_SPEED = constrain(SCROLLING_SPEED+1, 1, 5);
          scrollBlink(SCROLLING_SPEED);
        }
        else {
          for (int i = 0; i < SCROLLING_SPEED; i++) {
            BootKeyboard.write(KEY_UP_ARROW);
          }
        }
        break;
      case 1:
        BootKeyboard.write(KEY_RIGHT_ARROW);
        break;
    }
}

void ENC_2_LEFT() {
 switch(MODE) {
      case 0:
        BootKeyboard.write(KEY_LEFT_ARROW);
        break;
      case 1:
        if (SHIFT) {
          SCROLLING_SPEED = constrain(SCROLLING_SPEED-1, 1, 5);
          scrollBlink(SCROLLING_SPEED);
        }
        else {
          for (int i = 0; i < SCROLLING_SPEED; i++) {
            BootKeyboard.write(KEY_DOWN_ARROW);
          }
        }
        break;
    }
}
void ENC_2_RIGHT() {
switch(MODE) {
      case 0:
        BootKeyboard.write(KEY_RIGHT_ARROW);
        break;
      case 1:
        if (SHIFT) {
          SCROLLING_SPEED = constrain(SCROLLING_SPEED+1, 1, 5);
          scrollBlink(SCROLLING_SPEED);
        }
        else {
          for (int i = 0; i < SCROLLING_SPEED; i++) {
            BootKeyboard.write(KEY_UP_ARROW);
          }
        }
        break;
    }
}

void ENC_3_LEFT() {
 switch(MODE) {
      case 1:
        Consumer.write(MEDIA_VOL_DOWN);
        break;
      case 2:
        BootKeyboard.press(KEY_LEFT_CTRL);
        BootKeyboard.write(HID_KEYBOARD_MINUS_AND_UNDERSCORE);
        BootKeyboard.releaseAll();
        break;
    }
}
void ENC_3_RIGHT() {
  switch(MODE) {
      case 1:
        Consumer.write(MEDIA_VOL_UP);
        break;
      case 2:
        BootKeyboard.press(KEY_LEFT_CTRL);
        BootKeyboard.write(HID_KEYBOARD_EQUALS_AND_PLUS);
        BootKeyboard.releaseAll();
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

  for(u8 i = 0; i < (mode + 1); i++) {
    TXLED1;
    delay(300);
    TXLED0;
    delay(300);
  }
}

void scrollBlink(int scrolling_speed) {
  for(int i = 0; i < 3; i++) {
    delay(200 / scrolling_speed);
    TXLED1;
    delay(200 / scrolling_speed);
    TXLED0;
  }
}

void doohickeyDebug() {
  Serial.println("button0: " + String(currentStates[0]));
  Serial.println("button1: " + String(currentStates[1]));
  Serial.println("button2: " + String(currentStates[2]));
  Serial.println("button3: " + String(currentStates[3]));
  Serial.println("enc_button0: " + String(currentStates[4]));
  Serial.println("enc_button1: " + String(currentStates[5]));
  Serial.println("enc_button2: " + String(currentStates[6]));
  Serial.println("enc_button3: " + String(currentStates[7]));
  Serial.println("enc_0: " + String(currentStates[8]));
  Serial.println("enc_1: " + String(currentStates[9]));
  Serial.println("enc_2: " + String(currentStates[10]));
  Serial.println("enc_3: " + String(currentStates[11]));
}

void updateCurrentStates() {
  currentStates[0] = digitalRead(BUTTON_0);
  currentStates[1] = digitalRead(BUTTON_1);
  currentStates[2] = digitalRead(BUTTON_2);
  currentStates[3] = digitalRead(BUTTON_3);
  currentStates[4] = !digitalRead(ENC_0_BUTTON);
  currentStates[5] = !digitalRead(ENC_1_BUTTON);
  currentStates[6] = !digitalRead(ENC_2_BUTTON);
  currentStates[7] = !digitalRead(ENC_3_BUTTON);
  currentStates[8] = (-1 * ENC_0.read()) / 4;
  currentStates[9] = (-1 * ENC_1.read()) / 4;
  currentStates[10] = ENC_2.read() / 4;
  currentStates[11] = ENC_3.read() / 4;
}

void updatePreviousStates() {
  for (int i = 0; i < sizeof(currentStates) / sizeof(int); i++) {
    previousStates[i] = currentStates[i];
  }
}

bool checkForModeChange() {
  timeSinceLastModeChange = millis() - lastModeChange;
  return currentStates[3] && currentStates[8] != previousStates[8] && timeSinceLastModeChange > 300;
}

void handleModeChange() {
    if (currentStates[8] > previousStates[8]) {
      MODE++;
    }
    else if (currentStates[8] < previousStates[8]) {
      MODE--;
    }
    MODE = MODE % NUM_MODES;
    modeBlink(MODE);
    lastModeChange = millis();
    updatePreviousStates();
    return;
}