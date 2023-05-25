#include <Arduino.h>

#include "actions.hpp"
#include "state.hpp"

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
  if(currentStates[3]) {SHIFT = true;} else {SHIFT = false;}

  // BUTTON_0
  if (currentStates[0] > previousStates[0]) {
    BUTTON_0_PRESS();
  }

  // BUTTON_1
  if (currentStates[1] > previousStates[1]) {
    BUTTON_1_PRESS();
  }

  // BUTTON_2
  if (currentStates[2] > previousStates[2]) {
    BUTTON_2_PRESS();
  }

  // ENC_0_BUTTON 
  if (currentStates[4] > previousStates[4]) {
    BUTTON_ENC_0_PRESS();
  }

  // ENC_1_BUTTON 
  if (currentStates[5] > previousStates[5]) {
    BUTTON_ENC_1_PRESS();
  }

  // ENC_2_BUTTON 
  if (currentStates[6] > previousStates[6]) {
    BUTTON_ENC_2_PRESS();
  }

  // ENC_3_BUTTON
  // always listen for press
  if (currentStates[7] > previousStates[7]) {
    BUTTON_ENC_3_PRESS();
  }
  // listen for release
  else if (currentStates[7] < previousStates[7]) {
    BUTTON_ENC_3_RELEASE();
  }

  // ENC_0 LEFT
  if (currentStates[8] < previousStates[8]) {
    ENC_0_LEFT();
  }

  // ENC_0 RIGHT 
  if (currentStates[8] > previousStates[8]) {
    ENC_0_RIGHT();
  }

  // ENC_1 LEFT
  if (currentStates[9] < previousStates[9]) {
    ENC_1_LEFT();
  }
  
  // ENC_1 RIGHT
  if (currentStates[9] > previousStates[9]) {
    ENC_1_RIGHT();
  }

  // ENC_2 LEFT
  if (currentStates[10] < previousStates[10]) {
    ENC_2_LEFT();
  }
  
  // ENC_2 RIGHT
  if (currentStates[10] > previousStates[10]) {
    ENC_2_RIGHT();
  }

  // ENC_3 LEFT
  if (currentStates[11] < previousStates[11]) {
    ENC_3_LEFT();
  }
  
  // ENC_3 RIGHT
  if (currentStates[11] > previousStates[11]) {
    ENC_3_RIGHT();
  }

  updatePreviousStates();

  long t1 = micros();
  int delta = t1 - t0;
  Serial.println("delta: " + String(delta) + " microseconds");
  Serial.println("MODE: " + modeSate_toString(modeState));
  
  delayMicroseconds(10000 - delta);
}