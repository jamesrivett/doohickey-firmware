#include "inputs.hpp"
#include "actions.hpp"
#include "state.hpp"
#include "blink.hpp"

#include <Arduino.h>

void doohickeyDebug(int* states) {
  Serial.println("button0: " + String(states[0]));
  Serial.println("button1: " + String(states[1]));
  Serial.println("button2: " + String(states[2]));
  Serial.println("button3: " + String(states[3]));
  Serial.println("enc_button0: " + String(states[4]));
  Serial.println("enc_button1: " + String(states[5]));
  Serial.println("enc_button2: " + String(states[6]));
  Serial.println("enc_button3: " + String(states[7]));
  Serial.println("enc_0: " + String(states[8]));
  Serial.println("enc_1: " + String(states[9]));
  Serial.println("enc_2: " + String(states[10]));
  Serial.println("enc_3: " + String(states[11]));
}

inline void updateCurrentStates() {
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

inline void updatePreviousStates() {
  for (int i = 0; i < sizeof(currentStates) / sizeof(int); i++) {
    previousStates[i] = currentStates[i];
  }
}

inline bool checkForModeChange() {
  timeSinceLastModeChange = millis() - lastModeChange;
  return currentStates[3] && currentStates[8] != previousStates[8] && timeSinceLastModeChange > 300;
}


void setup() { 
  init();
}

void loop() {
  long t0 = millis();
  updateCurrentStates();

  // MODE CHANGE CHECK
  if (checkForModeChange()) {
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

  // SHIFT CHECK
  if(currentStates[3]) {shift = true;} else {shift = false;}

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
    ENC_0_RIGHT();
  }

  // ENC_2 LEFT
  if (currentStates[10] < previousStates[10]) {
    ENC_2_LEFT();
  }
  
  // ENC_2 RIGHT
  if (currentStates[10] > previousStates[10]) {
    ENC_0_RIGHT();
  }

  // ENC_3 LEFT
  if (currentStates[11] < previousStates[11]) {
    ENC_3_LEFT();
  }
  
  // ENC_3 RIGHT
  if (currentStates[11] > previousStates[11]) {
    ENC_0_RIGHT();
  }

  updatePreviousStates();

  long t1 = millis();
  int delta = t1 - t0;
  Serial.println("delta: " + String(delta));
  Serial.println("MODE: " + String(MODE));

  delay(10);
}