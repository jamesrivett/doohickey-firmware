#include <Encoder.h>
#include "inputs.hpp"

int BUTTON_0 = 18;
int BUTTON_1 = 15;
int BUTTON_2 = 14;
int BUTTON_3 = 7;

int ENC_0_BUTTON = 19;
int ENC_1_BUTTON = 20;
int ENC_2_BUTTON = 21;
int ENC_3_BUTTON = 16;

int ENC_0_CLK = 1;
int ENC_0_DT  = 6;
int ENC_1_CLK = 0;
int ENC_1_DT  = 5;
int ENC_2_CLK = 3;
int ENC_2_DT  = 9;
int ENC_3_CLK = 2;
int ENC_3_DT  = 10;

Encoder ENC_0 = Encoder(ENC_0_CLK, ENC_0_DT);
Encoder ENC_1 = Encoder(ENC_1_CLK, ENC_1_DT);
Encoder ENC_2 = Encoder(ENC_2_CLK, ENC_2_DT);
Encoder ENC_3 = Encoder(ENC_3_CLK, ENC_3_DT);