#include <Arduino.h>

#include "state.h"
#include "inputs.hpp"
#include "actions.h"

bool SHIFT = false;

int SCROLLING_SPEED = 3; 

InputStateFrame currentStates;
InputStateFrame previousStates;

void captureInputStateFrame(InputStateFrame* frame) {
  frame->BUTTON_0 = !digitalRead(BUTTON_0);
  frame->BUTTON_1 = !digitalRead(BUTTON_1);
  frame->BUTTON_2 = !digitalRead(BUTTON_2);
  frame->BUTTON_3 = !digitalRead(BUTTON_3);
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

void compareInputStateFrames(InputStateFrame* previousFrame, InputStateFrame* currentFrame) {
  // SHIFT CHECK
  if(currentFrame->BUTTON_3) {SHIFT = true;} else {SHIFT = false;}
  // BUTTON_0
  if (currentFrame->BUTTON_0 > previousFrame->BUTTON_0) {
    BUTTON_0_PRESS();
  }
  // BUTTON_1
  if (currentFrame->BUTTON_1 > previousFrame->BUTTON_1) {
    BUTTON_1_PRESS();
  }
  if (currentFrame->BUTTON_2 > previousFrame->BUTTON_2) {
    BUTTON_2_PRESS();
  }
  // ENC_0_BUTTON 
  if (currentFrame->ENC_0_BUTTON > previousFrame->ENC_0_BUTTON) {
    BUTTON_ENC_0_PRESS();
  }
  // ENC_1_BUTTON 
  if (currentFrame->ENC_1_BUTTON > previousFrame->ENC_1_BUTTON) {
    BUTTON_ENC_1_PRESS();
  }
  // ENC_2_BUTTON 
  if (currentFrame->ENC_2_BUTTON > previousFrame->ENC_2_BUTTON) {
    BUTTON_ENC_2_PRESS();
  }
  // ENC_3_BUTTON
  if (currentFrame->ENC_3_BUTTON > previousFrame->ENC_3_BUTTON) {
    BUTTON_ENC_3_PRESS();
  }
  // ENC_0 LEFT
  if (currentFrame->ENC_0 < previousFrame->ENC_0) {
    ENC_0_LEFT();
  }
  // ENC_0 RIGHT 
  if (currentFrame->ENC_0 > previousFrame->ENC_0) {
    ENC_0_RIGHT();
  }
  // ENC_1 LEFT
  if (currentFrame->ENC_1 < previousFrame->ENC_1) {
    ENC_1_LEFT();
  }
  // ENC_1 RIGHT
  if (currentFrame->ENC_1 > previousFrame->ENC_1) {
    ENC_1_RIGHT();
  }
  // ENC_2 LEFT
  if (currentFrame->ENC_2 < previousFrame->ENC_2) {
    ENC_2_LEFT();
  }
  // ENC_2 RIGHT
  if (currentFrame->ENC_2 > previousFrame->ENC_2) {
    ENC_2_RIGHT();
  }
  // ENC_3 LEFT
  if (currentFrame->ENC_3 < previousFrame->ENC_3) {
    ENC_3_LEFT();
  }
  // ENC_3 RIGHT
  if (currentFrame->ENC_3 > previousFrame->ENC_3) {
    ENC_3_RIGHT();
  }
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