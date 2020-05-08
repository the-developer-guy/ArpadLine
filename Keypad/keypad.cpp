#include "keypad.h"

Keypad::Keypad(int row_1, int row_2, int row_3, int row_4, 
         int column_1, int column_2, int column_3, int column_4):
         row{row_1, row_2, row_3, row_4},
         column{column_1, column_2, column_3, column_4}{
  type = Keypad_4_4;
  initIo();
}

         
Keypad::Keypad(int row_1, int row_2, int row_3, int row_4, 
         int column_1, int column_2, int column_3):
         row{row_1, row_2, row_3, row_4},
         column{column_1, column_2, column_3, -1}{
  type = Keypad_4_3;
  initIo();
}

void Keypad::initIo(void){
  for(int i = 0; i < 4; i++){
    pinMode(row[i], OUTPUT);  
    digitalWrite(row[i], HIGH);
  }
  for(int i = 0; i < type; i++){
    pinMode(column[i], INPUT_PULLUP);
  }
}

bool Keypad::addressLine(unsigned int line){
  bool success = false;
  for(int i = 0; i < 4; i++){
    digitalWrite(row[i], HIGH);  
  }
  if(line < 4){
    digitalWrite(row[line], LOW);
    success = true;
  }
  return success;
}

char Keypad::presseddButton(void){
  char button = KEYPAD_NONE;
  bool buttonSet = false;
  // Iterate through rows
  for(int r = 0; r < 4; r++){
    addressLine(r);
    if(button == KEYPAD_NONE){
      // Check columns
      for(int col = 0; col < type; col++){
        if(digitalRead(column[col]) == LOW){
          if(buttonSet == true){
            button = KEYPAD_INVALID;
          }
          else{
            buttonSet = true;
            button = keymap[r][col];
          }
        }
      }
    }
  }
  return button;
}
