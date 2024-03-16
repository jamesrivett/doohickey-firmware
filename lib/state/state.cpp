#include <Arduino.h>

#include "state.hpp"
#include "actions.hpp"
#include "inputs.hpp"

bool SHIFT = false;
int NUM_MODES = 3;

int SCROLLING_SPEED = 3; 

long lastModeChange = 0;
long timeSinceLastModeChange = 0;

int currentStates[] = {0,0,0,0,0,0,0,0,0,0,0,0};
int previousStates[] = {0,0,0,0,0,0,0,0,0,0,0,0};

ModeState modeState;

void updateCurrentStates() {
  currentStates[0] = digitalRead(BUTTON_0);
  currentStates[1] = digitalRead(BUTTON_1);
  currentStates[2] = digitalRead(BUTTON_2);
  currentStates[3] = digitalRead(BUTTON_3);
  currentStates[4] = !digitalRead(ENC_0_BUTTON);
  currentStates[5] = !digitalRead(ENC_1_BUTTON);
  currentStates[6] = !digitalRead(ENC_2_BUTTON);
  currentStates[7] = !digitalRead(ENC_3_BUTTON);
  noInterrupts();
  currentStates[8] = (-1 * ENC_0.read()) / 4;
  currentStates[9] = (-1 * ENC_1.read()) / 4;
  currentStates[10] = ENC_2.read() / 4;
  currentStates[11] = ENC_3.read() / 4;
  interrupts();
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
    modeState = ModeState(constrain(modeState + 1, 0, NUM_MODES - 1));
  }
  else if (currentStates[8] < previousStates[8]) {
    modeState = ModeState(constrain(modeState - 1, 0, NUM_MODES - 1));
  }
  modeBlink(modeState);
  lastModeChange = millis();
  updatePreviousStates();
  return;
}