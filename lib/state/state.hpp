#pragma once

enum ModeState {
    normal    = 0,
    lefty     = 1,
    photoshop = 2
};

struct InputStates {
  bool BUTTON_0;
  bool BUTTON_1;
  bool BUTTON_2;
  bool BUTTON_3;
  bool ENC_0_BUTTON;
  bool ENC_1_BUTTON;
  bool ENC_2_BUTTON;
  bool ENC_3_BUTTON;
  int ENC_0;
  int ENC_1;
  int ENC_2;
  int ENC_3;
};

extern bool SHIFT;
extern ModeState modeState;
extern int NUM_MODES;
extern int SCROLLING_SPEED;
extern long lastModeChange;
extern long timeSinceLastModeChange;
extern InputStates previousStates;
extern InputStates currentStates;

void updateCurrentStates();
void updatePreviousStates();
bool checkForModeChange();
void handleModeChange();