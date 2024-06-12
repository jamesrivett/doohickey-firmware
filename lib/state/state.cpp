#include <Arduino.h>

#include "state.h"
#include "inputs.h"

bool SHIFT = false;

int SCROLLING_SPEED = 3; 

InputStateFrame currentStates;
InputStateFrame previousStates;

void captureInputStateFrame(InputStateFrame* frame) {
  frame->BUTTON_0 = digitalRead(BUTTON_0);
  frame->BUTTON_1 = digitalRead(BUTTON_1);
  frame->BUTTON_2 = digitalRead(BUTTON_2);
  frame->BUTTON_3 = digitalRead(BUTTON_3);
  frame->ENC_0_BUTTON = !digitalRead(ENC_0_BUTTON);
  frame->ENC_1_BUTTON = !digitalRead(ENC_1_BUTTON);
  frame->ENC_2_BUTTON = !digitalRead(ENC_2_BUTTON);
  frame->ENC_3_BUTTON = !digitalRead(ENC_3_BUTTON);
  noInterrupts();
  frame->ENC_0 = (-1 * ENC_0.read()) / 4;
  frame->ENC_1 = (-1 * ENC_1.read()) / 4;
  frame->ENC_2 = ENC_2.read() / 4;
  frame->ENC_3 = ENC_3.read() / 4;
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