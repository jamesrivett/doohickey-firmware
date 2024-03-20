#include <Arduino.h>

#include "state.h"
#include "actions.h"
#include "inputs.h"

bool SHIFT = false;
int NUM_MODES = 3;

int SCROLLING_SPEED = 3; 

long lastModeChange = 0;
long timeSinceLastModeChange = 0;

ModeState modeState;

InputStates currentStates;
InputStates previousStates;

void updateCurrentStates() {
  currentStates.BUTTON_0 = digitalRead(BUTTON_0);
  currentStates.BUTTON_1 = digitalRead(BUTTON_1);
  currentStates.BUTTON_2 = digitalRead(BUTTON_2);
  currentStates.BUTTON_3 = digitalRead(BUTTON_3);
  currentStates.ENC_0_BUTTON = !digitalRead(ENC_0_BUTTON);
  currentStates.ENC_1_BUTTON = !digitalRead(ENC_1_BUTTON);
  currentStates.ENC_2_BUTTON = !digitalRead(ENC_2_BUTTON);
  currentStates.ENC_3_BUTTON = !digitalRead(ENC_3_BUTTON);
  noInterrupts();
  currentStates.ENC_0 = (-1 * ENC_0.read()) / 4;
  currentStates.ENC_1 = (-1 * ENC_1.read()) / 4;
  currentStates.ENC_2 = ENC_2.read() / 4;
  currentStates.ENC_3 = ENC_3.read() / 4;
  interrupts();
}

void updatePreviousStates() {
  previousStates.BUTTON_0 = currentStates.BUTTON_0;
  previousStates.BUTTON_1 = currentStates.BUTTON_1;
  previousStates.BUTTON_2 = currentStates.BUTTON_2;
  previousStates.BUTTON_3 = currentStates.BUTTON_3;
  previousStates.ENC_0_BUTTON = currentStates.ENC_0_BUTTON;
  previousStates.ENC_1_BUTTON = currentStates.ENC_1_BUTTON;
  previousStates.ENC_2_BUTTON = currentStates.ENC_2_BUTTON;
  previousStates.ENC_3_BUTTON = currentStates.ENC_3_BUTTON;
  previousStates.ENC_0 = currentStates.ENC_0;
  previousStates.ENC_1 = currentStates.ENC_1;
  previousStates.ENC_2 = currentStates.ENC_2;
  previousStates.ENC_3 = currentStates.ENC_3;
}

bool checkForModeChange() {
  timeSinceLastModeChange = millis() - lastModeChange;
  return currentStates.BUTTON_3 && currentStates.ENC_0 != previousStates.ENC_0 && timeSinceLastModeChange > 300;
}

void handleModeChange() {
  if (currentStates.ENC_0 > previousStates.ENC_0) {
    modeState = ModeState(constrain(modeState + 1, 0, NUM_MODES - 1));
  }
  else if (currentStates.ENC_0 < previousStates.ENC_0) {
    modeState = ModeState(constrain(modeState - 1, 0, NUM_MODES - 1));
  }
  modeBlink(modeState);
  lastModeChange = millis();
  updatePreviousStates();
  return;
}