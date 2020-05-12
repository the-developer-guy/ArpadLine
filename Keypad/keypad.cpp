#include "keypad.h"

static char decodeButton(int row, int column){
  char c = '\0';
  switch(row){
    case 0:
      switch(column){
        case 0:
          c = '1';
          break;
        case 1:
          c = '2';
          break;
        case 2:
          c = '3';
          break;
        case 3:
          c = 'A';
          break;
      }
      break;
    case 1:
      switch(column){
        case 0:
          c = '4';
          break;
        case 1:
          c = '5';
          break;
        case 2:
          c = '6';
          break;
        case 3:
          c = 'B';
          break;
      }
      break;
    case 2:
      switch(column){
        case 0:
          c = '7';
          break;
        case 1:
          c = '8';
          break;
        case 2:
          c = '9';
          break;
        case 3:
          c = 'C';
          break;
      }
      break;
    case 3:
      switch(column){
        case 0:
          c = '*';
          break;
        case 1:
          c = '0';
          break;
        case 2:
          c = '#';
          break;
        case 3:
          c = 'D';
          break;
      }
      break;
  }
  return c;
}

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
  delayMicroseconds(10);
  return success;
}

char Keypad::pressedButton(void){
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
            button = decodeButton(r,col);
          }
        }
      }
    }
  }
  return button;
}
