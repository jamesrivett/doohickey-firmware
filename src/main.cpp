#include <pins.h>

#include <Arduino.h>
#include <Encoder.h>
#include <HID-Project.h>

Encoder ENC_0 = Encoder(ENC_0_CLK, ENC_0_DT);
Encoder ENC_1 = Encoder(ENC_1_CLK, ENC_1_DT);
Encoder ENC_2 = Encoder(ENC_2_CLK, ENC_2_DT);
Encoder ENC_3 = Encoder(ENC_3_CLK, ENC_3_DT);

int previousStates[12];

void doohickeyDebug(int* states) {
  Serial.println("button0: " + String(states[0]));
  Serial.println("button1: " + String(states[1]));
  Serial.println("button2: " + String(states[2]));
  Serial.println("button3: " + String(states[3]));
  Serial.println("enc_button0: " + String(states[4]));
  Serial.println("enc_button1: " + String(states[5]));
  Serial.println("enc_button2: " + String(states[6]));
  Serial.println("enc_button3: " + String(states[7]));
  Serial.println("enc_0: " + String(states[8]));
  Serial.println("enc_1: " + String(states[9]));
  Serial.println("enc_2: " + String(states[10]));
  Serial.println("enc_3: " + String(states[11]));
}

int* updateStates(int* states) {
  states[0] = digitalRead(BUTTON_0);
  states[1] = digitalRead(BUTTON_1);
  states[2] = digitalRead(BUTTON_2);
  states[3] = digitalRead(BUTTON_3);
  states[4] = !digitalRead(ENC_0_BUTTON);
  states[5] = !digitalRead(ENC_1_BUTTON);
  states[6] = !digitalRead(ENC_2_BUTTON);
  states[7] = !digitalRead(ENC_3_BUTTON);
  states[8] = (-1 * ENC_0.read());
  states[9] = (-1 * ENC_1.read());
  states[10] = ENC_2.read();
  states[11] = ENC_3.read();

  return states;
}

void setup() { Serial.begin(9600);
  BootKeyboard.begin();
  Consumer.begin();

  pinMode(BUTTON_0, INPUT);
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  pinMode(BUTTON_3, INPUT);
  pinMode(ENC_0_BUTTON, INPUT_PULLUP);
  pinMode(ENC_1_BUTTON, INPUT_PULLUP);
  pinMode(ENC_2_BUTTON, INPUT_PULLUP);
  pinMode(ENC_3_BUTTON, INPUT_PULLUP);
}

void loop() {
  int *currentStates = updateStates(previousStates);
  doohickeyDebug(currentStates);

  for (int i = 0; i < sizeof(currentStates) / sizeof(int); i++) {
    previousStates[i] = currentStates[i];
  }

  delay(50);
}