#pragma once

bool shift;
int MODE = 0;
int NUM_MODES = 3;

int SCROLLING_SPEED = 3; 

long lastModeChange = 0;
long timeSinceLastModeChange = 0;
int previousStates[12];
int currentStates[12];