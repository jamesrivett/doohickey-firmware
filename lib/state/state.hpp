#pragma once

enum ModeState {
    normal    = 0,
    lefty     = 1,
    photoshop = 2
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