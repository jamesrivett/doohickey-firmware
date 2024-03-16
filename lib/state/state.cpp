#include <Arduino.h>

#include "state.hpp"
#include "actions.hpp"
#include "inputs.hpp"

bool SHIFT = false;
int NUM_MODES = 3;

int SCROLLING_SPEED = 3; 

long lastModeChange = 0;
long timeSinceLastModeChange = 0;

ModeState modeState;

struct InputStates {
  bool state_BUTTON_0;
  bool state_BUTTON_1;
  bool state_BUTTON_2;
  bool state_BUTTON_3;
  bool state_ENC_0_BUTTON;
  bool state_ENC_1_BUTTON;
  bool state_ENC_2_BUTTON;
  bool state_ENC_3_BUTTON;
  int state_ENC_0;
  int state_ENC_1;
  int state_ENC_2;
  int state_ENC_3;
};

InputStates currentStates;
InputStates previousStates;

void updateCurrentStates() {
  currentStates.state_BUTTON_0 = digitalRead(BUTTON_0);
  currentStates.state_BUTTON_1 = digitalRead(BUTTON_1);
  currentStates.state_BUTTON_2 = digitalRead(BUTTON_2);
  currentStates.state_BUTTON_3 = digitalRead(BUTTON_3);
  currentStates.state_ENC_0_BUTTON = !digitalRead(ENC_0_BUTTON);
  currentStates.state_ENC_1_BUTTON = !digitalRead(ENC_1_BUTTON);
  currentStates.state_ENC_2_BUTTON = !digitalRead(ENC_2_BUTTON);
  currentStates.state_ENC_3_BUTTON = !digitalRead(ENC_3_BUTTON);
  noInterrupts();
  currentStates.state_ENC_0 = (-1 * ENC_0.read()) / 4;
  currentStates.state_ENC_1 = (-1 * ENC_1.read()) / 4;
  currentStates.state_ENC_2 = ENC_2.read() / 4;
  currentStates.state_ENC_3 = ENC_3.read() / 4;
  interrupts();
}

void updatePreviousStates() {
  currentStates.state_BUTTON_0 = previousStates.state_BUTTON_0;
  currentStates.state_BUTTON_1 = previousStates.state_BUTTON_1;
  currentStates.state_BUTTON_2 = previousStates.state_BUTTON_2;
  currentStates.state_BUTTON_3 = previousStates.state_BUTTON_3;
  currentStates.state_ENC_0_BUTTON = previousStates.state_ENC_0_BUTTON;
  currentStates.state_ENC_1_BUTTON = previousStates.state_ENC_1_BUTTON;
  currentStates.state_ENC_2_BUTTON = previousStates.state_ENC_2_BUTTON;
  currentStates.state_ENC_3_BUTTON = previousStates.state_ENC_3_BUTTON;
  currentStates.state_ENC_0 = previousStates.state_ENC_0;
  currentStates.state_ENC_1 = previousStates.state_ENC_1;
  currentStates.state_ENC_2 = previousStates.state_ENC_2;
  currentStates.state_ENC_3 = previousStates.state_ENC_3;
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