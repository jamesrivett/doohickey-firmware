#include <pins.h>

#include <Arduino.h>
#include <Encoder.h>
#include <HID-Project.h>

Encoder ENC_0 = Encoder(ENC_0_CLK, ENC_0_DT);
Encoder ENC_1 = Encoder(ENC_1_CLK, ENC_1_DT);
Encoder ENC_2 = Encoder(ENC_2_CLK, ENC_2_DT);
Encoder ENC_3 = Encoder(ENC_3_CLK, ENC_3_DT);

u8 mode = 0;
u8 NUM_MODES = 2;

long lastModeChange = 0;
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
  long t0 = millis();
  int currentStates[12];

  // check for mode change
  currentStates[0] = digitalRead(BUTTON_0);
  currentStates[7] = !digitalRead(ENC_3_BUTTON);
  long timeSinceLastModeChange = millis() - lastModeChange;
  if (currentStates[0] && currentStates[7] && timeSinceLastModeChange > 300) {
    mode++;
    mode = mode % NUM_MODES;
    lastModeChange = millis();
    return;
  }

  // BUTTON_0 (was already state-updated at mode change check)
  if (currentStates[0] > previousStates[0]) {
    switch(mode) {
      case 0:
        Consumer.write(CONSUMER_BROWSER_FORWARD);
        break;
    }
  }

  // BUTTON_1
  currentStates[1] = digitalRead(BUTTON_1);
  if (currentStates[1] > previousStates[1]) {
    switch(mode) {
      case 0:
        Consumer.write(CONSUMER_BROWSER_BACK);
        break;
    }
  }

  // BUTTON_2
  currentStates[2] = digitalRead(BUTTON_2);
  if (currentStates[2] > previousStates[2]) {
    switch(mode) {
      case 1:
        Consumer.write(CONSUMER_BROWSER_FORWARD);
        break;
    }
  }

  // BUTTON_3
  currentStates[3] = digitalRead(BUTTON_3);
  if (currentStates[3] > previousStates[3]) {
    switch(mode) {
      case 1:
        Consumer.write(CONSUMER_BROWSER_BACK);
        break;
    }
  }





  // ENC_0_BUTTON 
  currentStates[4] = !digitalRead(ENC_0_BUTTON);
  if (currentStates[4] > previousStates[4]) {
    switch(mode) {}
    Consumer.write(MEDIA_VOL_MUTE);
  }

  // ENC_0 LEFT
  currentStates[8] = (-1 * ENC_0.read()) / 4;
  if (currentStates[8] < previousStates[8]) {
    switch(mode) {
      case 0:
        Consumer.write(MEDIA_VOL_DOWN);
        break;
    }
  }

  // ENC_0 RIGHT 
  currentStates[8] = (-1 * ENC_0.read()) / 4;
  if (currentStates[8] > previousStates[8]) {
    switch(mode) {
      case 0:
        Consumer.write(MEDIA_VOL_UP);
        break;
    }
  }

  // ENC_1_BUTTON 
  currentStates[5] = !digitalRead(ENC_1_BUTTON);
  if (currentStates[5] > previousStates[5]) {
    switch(mode) {
      case 0:
        BootKeyboard.write(KEY_ENTER);
        break;
    }
  }

  // ENC_1 LEFT
  currentStates[9] = (-1 * ENC_1.read()) / 4;
  if (currentStates[9] < previousStates[9]) {
    switch(mode) {
      case 0:
        BootKeyboard.write(KEY_DOWN_ARROW);
        break;
      case 1:
        BootKeyboard.write(KEY_LEFT_ARROW);
        break;
    }
  }
  
  // ENC_1 RIGHT
  currentStates[9] = (-1 * ENC_1.read()) / 4;
  if (currentStates[9] > previousStates[9]) {
    switch(mode) {
      case 0:
        BootKeyboard.write(KEY_UP_ARROW);
        break;
      case 1:
        BootKeyboard.write(KEY_RIGHT_ARROW);
        break;
    }
  }

  // ENC_2_BUTTON 
  currentStates[6] = !digitalRead(ENC_2_BUTTON);
  if (currentStates[6] > previousStates[6]) {
    switch(mode) {
      case 1:
        BootKeyboard.write(KEY_ENTER);
        break;
    }
  }

  // ENC_2 LEFT
  currentStates[10] = ENC_2.read() / 4;
  if (currentStates[10] < previousStates[10]) {
    switch(mode) {
      case 0:
        BootKeyboard.write(KEY_LEFT_ARROW);
        break;
      case 1:
        BootKeyboard.write(KEY_DOWN_ARROW);
        break;
    }
  }
  
  // ENC_2 RIGHT
  currentStates[10] = ENC_2.read() / 4;
  if (currentStates[10] > previousStates[10]) {
    switch(mode) {
      case 0:
        BootKeyboard.write(KEY_RIGHT_ARROW);
        break;
      case 1:
        BootKeyboard.write(KEY_UP_ARROW);
        break;
    }
  }

  // ENC_3_BUTTON (was already state-updated at mode change check)
  if (currentStates[7] > previousStates[7]) {
    switch(mode) {}
    
  }

  // ENC_3 LEFT
  currentStates[11] = ENC_3.read() / 4;
  if (currentStates[11] < previousStates[11]) {
    switch(mode) {
      case 1:
        Consumer.write(MEDIA_VOL_DOWN);
        break;
    }
  }
  
  // ENC_3 RIGHT
  currentStates[11] = ENC_3.read() / 4;
  if (currentStates[11] > previousStates[11]) {
    switch(mode) {
      case 1:
        Consumer.write(MEDIA_VOL_UP);
      break;
    }
  }


  // update previous states
  for (int i = 0; i < sizeof(currentStates) / sizeof(int); i++) {
    previousStates[i] = currentStates[i];
  }


  long t1 = millis();
  int delta = t1 - t0;
  Serial.println("delta: " + String(delta));
  Serial.println("mode: " + String(mode));

  delay(10);
}