#include <pins.h>

#include <Arduino.h>
#include <Encoder.h>
#include <HID-Project.h>

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

Encoder ENC_0 = Encoder(ENC_0_CLK, ENC_0_DT);
Encoder ENC_1 = Encoder(ENC_1_CLK, ENC_1_DT);
Encoder ENC_2 = Encoder(ENC_2_CLK, ENC_2_DT);
Encoder ENC_3 = Encoder(ENC_3_CLK, ENC_3_DT);

void loop() {
  Serial.println("button0: " + String(digitalRead(BUTTON_0)));
  Serial.println("button1: " + String(digitalRead(BUTTON_1)));
  Serial.println("button2: " + String(digitalRead(BUTTON_2)));
  Serial.println("button3: " + String(digitalRead(BUTTON_3)));
  Serial.println("enc_button0: " + String(digitalRead(ENC_0_BUTTON)));
  Serial.println("enc_button1: " + String(digitalRead(ENC_1_BUTTON)));
  Serial.println("enc_button2: " + String(digitalRead(ENC_2_BUTTON)));
  Serial.println("enc_button3: " + String(digitalRead(ENC_3_BUTTON)));
  Serial.println("enc_0: " + String(ENC_0.read()));
  Serial.println("enc_1: " + String(ENC_1.read()));
  Serial.println("enc_2: " + String(ENC_2.read()));
  Serial.println("enc_3: " + String(ENC_3.read()));
  delay(50);
}