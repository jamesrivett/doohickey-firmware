#include <Arduino.h>
#include <HID-Project.h>
#include <Encoder.h>

#include "inputs.hpp"
#include "actions.h"
#include "state.h"

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