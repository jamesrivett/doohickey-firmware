#pragma once
#include <Encoder.h>

const int BUTTON_0 = 15;
const int BUTTON_1 = 14;
const int BUTTON_2 = 16;
const int BUTTON_3 = 10;

const int ENC_0_BUTTON = 4;
const int ENC_1_BUTTON = 5;
const int ENC_2_BUTTON = 8;
const int ENC_3_BUTTON = 9;

const int ENC_0_CLK = 1;
const int ENC_0_DT  = 21;
const int ENC_1_CLK = 0;
const int ENC_1_DT  = 20;
const int ENC_2_CLK = 3;
const int ENC_2_DT  = 2;
const int ENC_3_CLK = 7;
const int ENC_3_DT  = 6;

Encoder ENC_0 = Encoder(ENC_0_CLK, ENC_0_DT);
Encoder ENC_1 = Encoder(ENC_1_CLK, ENC_1_DT);
Encoder ENC_2 = Encoder(ENC_2_CLK, ENC_2_DT);
Encoder ENC_3 = Encoder(ENC_3_CLK, ENC_3_DT);