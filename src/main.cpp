#include <pins.h>

#include <Arduino.h>
#include <Encoder.h>
#include <HID-Project.h>

Encoder ENC_0 = Encoder(ENC_0_CLK, ENC_0_DT);
Encoder ENC_1 = Encoder(ENC_1_CLK, ENC_1_DT);
Encoder ENC_2 = Encoder(ENC_2_CLK, ENC_2_DT);
Encoder ENC_3 = Encoder(ENC_3_CLK, ENC_3_DT);

bool shift;
u8 mode = 1;
u8 NUM_MODES = 2;

long lastModeChange = 0;
long timeSinceLastModeChange = 0;
int previousStates[12];
int currentStates[12];

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

inline void updateCurrentStates() {
  currentStates[0] = digitalRead(BUTTON_0);
  currentStates[1] = digitalRead(BUTTON_1);
  currentStates[2] = digitalRead(BUTTON_2);
  currentStates[3] = digitalRead(BUTTON_3);
  currentStates[4] = !digitalRead(ENC_0_BUTTON);
  currentStates[5] = !digitalRead(ENC_1_BUTTON);
  currentStates[6] = !digitalRead(ENC_2_BUTTON);
  currentStates[7] = !digitalRead(ENC_3_BUTTON);
  currentStates[8] = (-1 * ENC_0.read()) / 4;
  currentStates[9] = (-1 * ENC_1.read()) / 4;
  currentStates[10] = ENC_2.read() / 4;
  currentStates[11] = ENC_3.read() / 4;
}

inline void updatePreviousStates() {
  for (int i = 0; i < sizeof(currentStates) / sizeof(int); i++) {
    previousStates[i] = currentStates[i];
  }
}

inline bool checkForModeChange() {
  timeSinceLastModeChange = millis() - lastModeChange;
  return currentStates[3] && currentStates[8] != previousStates[8] && timeSinceLastModeChange > 300;
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
  updateCurrentStates();

  // MODE CHANGE CHECK
  if (checkForModeChange()) {
    if (currentStates[8] > previousStates[8]) {
      mode++;
    }
    else if (currentStates[8] < previousStates[8]) {
      mode--;
    }
    mode = mode % NUM_MODES;

    TXLED1;
    delay(50);
    TXLED0;
    delay(50);
    TXLED1;
    delay(50);
    TXLED0;

    for(u8 i = 0; i < (mode + 1); i++) {
      delay(500);
      TXLED1;
      delay(500);
      TXLED0;
    }

    lastModeChange = millis();
    updatePreviousStates();
    return;
  }

  // SHIFT CHECK
  if(currentStates[3]) {shift = true;} else {shift = false;}

  // BUTTON_0
  if (currentStates[0] > previousStates[0]) {
    if (shift) {
      Consumer.write(MEDIA_NEXT);
    }
    else {
      Consumer.write(CONSUMER_BROWSER_FORWARD);
    }
  }

  // BUTTON_1
  if (currentStates[1] > previousStates[1]) {
    if (shift) {
      Consumer.write(MEDIA_PLAY_PAUSE);
    }
    else {
      Consumer.write(CONSUMER_BROWSER_BACK);
    }
  }

  // BUTTON_2
  if (currentStates[2] > previousStates[2]) {
    if (shift) {
      Consumer.write(MEDIA_PREVIOUS);
    }
    else {
      Consumer.write(CONSUMER_BROWSER_FORWARD);
    }
  }



  // ENC_0_BUTTON 
  if (currentStates[4] > previousStates[4]) {
    switch(mode) {
      case 0:
        Consumer.write(MEDIA_VOL_MUTE);
        break;
      case 1:
        if (shift) {
          BootKeyboard.press(KEY_RIGHT_ALT);
          BootKeyboard.write(KEY_RIGHT_BRACE);
          BootKeyboard.release(KEY_RIGHT_ALT);
        }
        else {
          BootKeyboard.press(KEY_RIGHT_ALT);
          BootKeyboard.write(KEY_LEFT_BRACE);
          BootKeyboard.release(KEY_RIGHT_ALT);
        }
        break;
    }
  }

  // ENC_0 LEFT
  if (currentStates[8] < previousStates[8]) {
    switch(mode) {
      case 0:
        Consumer.write(MEDIA_VOL_DOWN);
        break;
    }
  }

  // ENC_0 RIGHT 
  if (currentStates[8] > previousStates[8]) {
    switch(mode) {
      case 0:
        Consumer.write(MEDIA_VOL_UP);
        break;
    }
  }

  // ENC_1_BUTTON 
  if (currentStates[5] > previousStates[5]) {
    switch(mode) {
      case 0:
        BootKeyboard.write(KEY_ENTER);
        break;
    }
  }

  // ENC_1 LEFT
  if (currentStates[9] < previousStates[9]) {
    switch(mode) {
      case 0:
        BootKeyboard.write(KEY_UP_ARROW);
        break;
      case 1:
        BootKeyboard.write(KEY_LEFT_ARROW);
        break;
    }
  }
  
  // ENC_1 RIGHT
  if (currentStates[9] > previousStates[9]) {
    switch(mode) {
      case 0:
        BootKeyboard.write(KEY_DOWN_ARROW);
        break;
      case 1:
        BootKeyboard.write(KEY_RIGHT_ARROW);
        break;
    }
  }

  // ENC_2_BUTTON 
  if (currentStates[6] > previousStates[6]) {
    switch(mode) {
      case 1:
        BootKeyboard.write(KEY_ENTER);
        break;
    }
  }

  // ENC_2 LEFT
  if (currentStates[10] < previousStates[10]) {
    switch(mode) {
      case 0:
        BootKeyboard.write(KEY_LEFT_ARROW);
        break;
      case 1:
        BootKeyboard.write(KEY_UP_ARROW);
        break;
    }
  }
  
  // ENC_2 RIGHT
  if (currentStates[10] > previousStates[10]) {
    switch(mode) {
      case 0:
        BootKeyboard.write(KEY_RIGHT_ARROW);
        break;
      case 1:
        BootKeyboard.write(KEY_DOWN_ARROW);
        break;
    }
  }

  // ENC_3_BUTTON
  if (currentStates[7] > previousStates[7]) {
    switch(mode) {
      case 0:
        if (shift) {
          BootKeyboard.press(KEY_RIGHT_ALT);
          BootKeyboard.write(KEY_RIGHT_BRACE);
          BootKeyboard.release(KEY_RIGHT_ALT);
        }
        else {
          BootKeyboard.press(KEY_RIGHT_ALT);
          BootKeyboard.write(KEY_LEFT_BRACE);
          BootKeyboard.release(KEY_RIGHT_ALT);
        }
        break;
      case 1:
        Consumer.write(MEDIA_VOL_MUTE);
        break;
    }
  }

  // ENC_3 LEFT
  if (currentStates[11] < previousStates[11]) {
    switch(mode) {
      case 1:
        Consumer.write(MEDIA_VOL_DOWN);
        break;
    }
  }
  
  // ENC_3 RIGHT
  if (currentStates[11] > previousStates[11]) {
    switch(mode) {
      case 1:
        Consumer.write(MEDIA_VOL_UP);
      break;
    }
  }

  updatePreviousStates();

  long t1 = millis();
  int delta = t1 - t0;
  Serial.println("delta: " + String(delta));
  Serial.println("mode: " + String(mode));

  delay(10);
}