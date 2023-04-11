#include <Arduino.h>

inline void modeBlink(int mode) {
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