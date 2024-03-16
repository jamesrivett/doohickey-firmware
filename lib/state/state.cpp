#include "state.hpp"

bool SHIFT = false;
int NUM_MODES = 3;

int SCROLLING_SPEED = 3; 

long lastModeChange = 0;
long timeSinceLastModeChange = 0;

int currentStates[] = {0,0,0,0,0,0,0,0,0,0,0,0};
int previousStates[] = {0,0,0,0,0,0,0,0,0,0,0,0};

ModeState modeState;