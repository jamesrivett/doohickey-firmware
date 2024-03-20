#include <Arduino.h>

#include "actions.h"
#include "state.h"

inline String modeSate_toString(ModeState ms) {
  if(ms == normal){return "normal";}
  if(ms == lefty){return "lefty";}
  if(ms == photoshop){return "photoshop";}
}

void setup() { 
  doohickeyInit();
}

void loop() {
  long t0 = micros();
  updateCurrentStates();

  // MODE CHANGE CHECK
  if (checkForModeChange()) {
    handleModeChange();
  }

  // SHIFT CHECSHIFTK
  if(currentStates.BUTTON_3) {SHIFT = true;} else {SHIFT = false;}

  // BUTTON_0
  if (currentStates.BUTTON_0 > previousStates.BUTTON_0) {
    BUTTON_0_PRESS();
  }

  // BUTTON_1
  if (currentStates.BUTTON_1 > previousStates.BUTTON_1) {
    BUTTON_1_PRESS();
  }

  // BUTTON_2
  if (currentStates.BUTTON_2 > previousStates.BUTTON_2) {
    BUTTON_2_PRESS();
  }

  // ENC_0_BUTTON 
  if (currentStates.ENC_0_BUTTON > previousStates.ENC_0_BUTTON) {
    BUTTON_ENC_0_PRESS();
  }

  // ENC_1_BUTTON 
  if (currentStates.ENC_1_BUTTON > previousStates.ENC_1_BUTTON) {
    BUTTON_ENC_1_PRESS();
  }

  // ENC_2_BUTTON 
  if (currentStates.ENC_2_BUTTON > previousStates.ENC_2_BUTTON) {
    BUTTON_ENC_2_PRESS();
  }

  // ENC_3_BUTTON
  // always listen for press
  if (currentStates.ENC_3_BUTTON > previousStates.ENC_3_BUTTON) {
    BUTTON_ENC_3_PRESS();
  }
  // listen for release
  else if (currentStates.ENC_3_BUTTON < previousStates.ENC_3_BUTTON) {
    BUTTON_ENC_3_RELEASE();
  }

  // ENC_0 LEFT
  if (currentStates.ENC_0 < previousStates.ENC_0) {
    ENC_0_LEFT();
  }

  // ENC_0 RIGHT 
  if (currentStates.ENC_0 > previousStates.ENC_0) {
    ENC_0_RIGHT();
  }

  // ENC_1 LEFT
  if (currentStates.ENC_1 < previousStates.ENC_1) {
    ENC_1_LEFT();
  }
  
  // ENC_1 RIGHT
  if (currentStates.ENC_1 > previousStates.ENC_1) {
    ENC_1_RIGHT();
  }

  // ENC_2 LEFT
  if (currentStates.ENC_2 < previousStates.ENC_2) {
    ENC_2_LEFT();
  }
  
  // ENC_2 RIGHT
  if (currentStates.ENC_2 > previousStates.ENC_2) {
    ENC_2_RIGHT();
  }

  // ENC_3 LEFT
  if (currentStates.ENC_3 < previousStates.ENC_3) {
    ENC_3_LEFT();
  }
  
  // ENC_3 RIGHT
  if (currentStates.ENC_3 > previousStates.ENC_3) {
    ENC_3_RIGHT();
  }

  updatePreviousStates();

  long t1 = micros();
  int delta = t1 - t0;
  float deltaMillis = float(delta) / 1000;
  Serial.println("delta: " + String(deltaMillis) + " miliseconds");
  Serial.println("MODE: " + modeSate_toString(modeState));
  
  delayMicroseconds(10000 - delta);
}