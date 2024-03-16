#pragma once
void doohickeyInit();

void BUTTON_0_PRESS();
void BUTTON_1_PRESS();
void BUTTON_2_PRESS();
void BUTTON_ENC_0_PRESS();
void BUTTON_ENC_1_PRESS();
void BUTTON_ENC_2_PRESS();
void BUTTON_ENC_3_PRESS();
void BUTTON_ENC_3_RELEASE();

void ENC_0_LEFT();
void ENC_1_LEFT();
void ENC_2_LEFT();
void ENC_3_LEFT();
void ENC_0_RIGHT();
void ENC_1_RIGHT();
void ENC_2_RIGHT();
void ENC_3_RIGHT();

void modeBlink(int mode);

void scrollBlink(int scrolling_speed);
void doohickeyDebug();