#include "keypad.h"

Keypad mainPad(4, 5, 6, 7, 8, 9, 10, 11);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting");
}

void loop() {
  // put your main code here, to run repeatedly:
  char c = mainPad.pressedButton();
  if(c != KEYPAD_INVALID && c != KEYPAD_NONE){
    Serial.print(c);
    delay(100);
  }
}
