#include <HID-Project.h>
#include "inputs.hpp"
#include "actions.hpp"
#include "state.hpp"
#include "blink.hpp"

inline void init() {
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

inline void BUTTON_0_PRESS() {
    if (shift) {
      Consumer.write(HID_CONSUMER_AC_FORWARD);
    }
    else {
      Consumer.write(MEDIA_NEXT);
    }
}

inline void BUTTON_1_PRESS() {
    if (shift) {
    }
    else {
      Consumer.write(MEDIA_PLAY_PAUSE);
    }
}

inline void BUTTON_2_PRESS() {
    if (shift) {
      Consumer.write(HID_CONSUMER_AC_BACK);
    }
    else {
      Consumer.write(MEDIA_PREVIOUS);
    }
}

inline void BUTTON_ENC_0_PRESS() {
    switch(MODE) {
        case 0:
        Consumer.write(MEDIA_VOL_MUTE);
        break;
        case 1:
        if (shift) {
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

inline void BUTTON_ENC_1_PRESS() {
    switch(MODE) {
      case 0:
        BootKeyboard.write(KEY_ENTER);
        break;
    }
}

inline void BUTTON_ENC_2_PRESS() {
    switch(MODE) {
      case 1:
        BootKeyboard.write(KEY_ENTER);
        break;
    }
}

inline void BUTTON_ENC_3_PRESS() {
    switch(MODE) {
      case 0:
        if (shift) {
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

inline void BUTTON_ENC_3_RELEASE() {
    switch(MODE) {
      case 2:
        BootKeyboard.release(KEY_SPACE);
    }
}

inline void ENC_0_LEFT() {
    switch(MODE) {
      case 0:
        Consumer.write(MEDIA_VOL_DOWN);
        break;
      case 2:
        BootKeyboard.write(KEY_LEFT_BRACE);
        break;
    }
}
inline void ENC_0_RIGHT() {
    switch(MODE) {
      case 0:
        Consumer.write(MEDIA_VOL_UP);
        break;
      case 2:
        BootKeyboard.write(KEY_RIGHT_BRACE);
        break;
    }
}

inline void ENC_1_LEFT() {
    switch(MODE) {
      case 0:
        if (shift) {
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
inline void ENC_1_RIGHT() {
    switch(MODE) {
      case 0:
        if (shift) {
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

inline void ENC_2_LEFT() {
 switch(MODE) {
      case 0:
        BootKeyboard.write(KEY_LEFT_ARROW);
        break;
      case 1:
        if (shift) {
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
inline void ENC_2_RIGHT() {
switch(MODE) {
      case 0:
        BootKeyboard.write(KEY_RIGHT_ARROW);
        break;
      case 1:
        if (shift) {
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

inline void ENC_3_LEFT() {
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
inline void ENC_3_RIGHT() {
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