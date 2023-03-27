
#include <Arduino.h>
#include <Encoder.h>
#include <HID-Project.h>

Encoder myEnc(1, 7);
int lastButt = 1;
int lastBump = 0;

void setup() {
  Serial.begin(9600);
  BootKeyboard.begin();
  Consumer.begin();
  pinMode(10, INPUT_PULLUP);
}

void loop() {
  int currentState = myEnc.read();
  int currentButt = digitalRead(10);
  Serial.print(currentButt);
  int currentBump = (currentState - currentState % 4);

  if (lastBump > currentBump) {
    BootKeyboard.write(KEY_LEFT_ARROW);
  }
  if (lastBump < currentBump) {
    BootKeyboard.write(KEY_RIGHT_ARROW);
  }
  if (lastButt > currentButt) {
    Consumer.write(MEDIA_PLAY_PAUSE);
  }
  
  lastButt = currentButt;
  lastBump = currentBump;
  delay(100);
}