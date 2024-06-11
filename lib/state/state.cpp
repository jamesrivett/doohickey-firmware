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

InputStateFrame currentStates;
InputStateFrame previousStates;

void captureInputStateFrame(InputStateFrame* capturedState) {
  capturedState->BUTTON_0 = digitalRead(BUTTON_0);
  capturedState->BUTTON_1 = digitalRead(BUTTON_1);
  capturedState->BUTTON_2 = digitalRead(BUTTON_2);
  capturedState->BUTTON_3 = digitalRead(BUTTON_3);
  capturedState->ENC_0_BUTTON = !digitalRead(ENC_0_BUTTON);
  capturedState->ENC_1_BUTTON = !digitalRead(ENC_1_BUTTON);
  capturedState->ENC_2_BUTTON = !digitalRead(ENC_2_BUTTON);
  capturedState->ENC_3_BUTTON = !digitalRead(ENC_3_BUTTON);
  noInterrupts();
  capturedState->ENC_0 = (-1 * ENC_0.read()) / 4;
  capturedState->ENC_1 = (-1 * ENC_1.read()) / 4;
  capturedState->ENC_2 = ENC_2.read() / 4;
  capturedState->ENC_3 = ENC_3.read() / 4;
  interrupts();
}

void copyInputStateFrame(InputStateFrame* targetFrame, InputStateFrame* sourceFrame) {
  targetFrame->BUTTON_0 = sourceFrame->BUTTON_0;
  targetFrame->BUTTON_1 = sourceFrame->BUTTON_1;
  targetFrame->BUTTON_2 = sourceFrame->BUTTON_2;
  targetFrame->BUTTON_3 = sourceFrame->BUTTON_3;
  targetFrame->ENC_0_BUTTON = sourceFrame->ENC_0_BUTTON;
  targetFrame->ENC_1_BUTTON = sourceFrame->ENC_1_BUTTON;
  targetFrame->ENC_2_BUTTON = sourceFrame->ENC_2_BUTTON;
  targetFrame->ENC_3_BUTTON = sourceFrame->ENC_3_BUTTON;
  targetFrame->ENC_0 = sourceFrame->ENC_0;
  targetFrame->ENC_1 = sourceFrame->ENC_1;
  targetFrame->ENC_2 = sourceFrame->ENC_2;
  targetFrame->ENC_3 = sourceFrame->ENC_3;
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
  copyInputStateFrame(&previousStates, &currentStates);
  return;
}