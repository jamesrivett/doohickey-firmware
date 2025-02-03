#include <Arduino.h>
#include "actions.h"
#include "state.h"

void setup() { 
  doohickeyInit();
}

void loop() {
  long t0 = micros();
  captureInputStateFrame(&currentStates);
  compareInputStateFrames(&previousStates, &currentStates);
  copyInputStateFrame(&previousStates, &currentStates);
  long t1 = micros();
  int delta = t1 - t0;
  float deltaMillis = float(delta) / 1000;
  // Serial.println("delta: " + String(deltaMillis) + " miliseconds");
  // doohickeyDebug();
  delayMicroseconds(10000 - delta);
}