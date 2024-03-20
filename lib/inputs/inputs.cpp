#include <Encoder.h>
#include "inputs.h"

int BUTTON_0 = 15;
int BUTTON_1 = 14;
int BUTTON_2 = 16;
int BUTTON_3 = 10;

int ENC_0_BUTTON = 4;
int ENC_1_BUTTON = 5;
int ENC_2_BUTTON = 8;
int ENC_3_BUTTON = 9;

int ENC_0_CLK = 1;
int ENC_0_DT  = 21;
int ENC_1_CLK = 0;
int ENC_1_DT  = 20;
int ENC_2_CLK = 3;
int ENC_2_DT  = 2;
int ENC_3_CLK = 7;
int ENC_3_DT  = 6;

Encoder ENC_0 = Encoder(ENC_0_CLK, ENC_0_DT);
Encoder ENC_1 = Encoder(ENC_1_CLK, ENC_1_DT);
Encoder ENC_2 = Encoder(ENC_2_CLK, ENC_2_DT);
Encoder ENC_3 = Encoder(ENC_3_CLK, ENC_3_DT);