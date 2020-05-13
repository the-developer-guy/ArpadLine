#include "hd44780.h"

template <unsigned int W, unsigned int H>
HD44780<W, H>::HD44780(int enable, int registerSelect,
        int db7, int db6, int db5, int db4):
        dataPins{db7, db6, db5, db4, -1, -1, -1, -1}, mode_4pin(true),
        activeBuffer(true), rsPin(registerSelect), enablePin(enable), rwPin(-1), backlightPin(-1) {
  init();
}

template <unsigned int W, unsigned int H>
HD44780<W, H>::HD44780(int enable, int registerSelect, 
        int db7, int db6, int db5, int db4, int backlight):
        dataPins{db7, db6, db5, db4, -1, -1, -1, -1}, mode_4pin(true),
        activeBuffer(true), rsPin(registerSelect), enablePin(enable), rwPin(-1), backlightPin(backlight) {
  init();
}

template <unsigned int W, unsigned int H>
HD44780<W, H>::HD44780(int enable, int registerSelect, 
        int db7, int db6, int db5, int db4, int db3, int db2, int db1, int db0):
        dataPins{db7, db6, db5, db4, db3, db2, db1, db0}, mode_4pin(false),
        activeBuffer(true), rsPin(registerSelect), enablePin(enable), rwPin(-1), backlightPin(-1) {
  init();
}

template <unsigned int W, unsigned int H>
HD44780<W, H>::HD44780(int enable, int registerSelect, 
        int db7, int db6, int db5, int db4, int db3, int db2, int db1, int db0, int backlight):
        dataPins{db7, db6, db5, db4, db3, db2, db1, db0}, mode_4pin(false),
        activeBuffer(true), rsPin(registerSelect), enablePin(enable), rwPin(-1), backlightPin(backlight) {
  init();
}

template <unsigned int W, unsigned int H>
void HD44780<W, H>::init(void){
  clearDisplay();
  initIo();
  if(mode_4pin == true){
    digitalWrite(db7, HIGH);
    digitalWrite(db6, HIGH);
    digitalWrite(db5, LOW);
    digitalWrite(db4, LOW);
    clock();
    delayMicroseconds(4500);
    clock();
    delayMicroseconds(4500);
    clock();
    delayMicroseconds(150);
    digitalWrite(db7, HIGH);
    clock();
  }
  else{
    writeByte(0x30, false); // 8-bit mode 
  }
  writeByte(0x01, false); // clear display, return cursor
  writeByte(0x0c, false); // enable display, no cursor
  backlightOn();
}

template <unsigned int W, unsigned int H>
void HD44780<W, H>::initIo(void){
  for(int i = 0; i < 8; i++){
    if(dataPins[i] != -1){
      digitalWrite(dataPins[i], LOW);
      pinMode(dataPins[i], OUTPUT);  
    }
  }
  digitalWrite(rsPin, LOW);
  pinMode(rsPin, OUTPUT);
  digitalWrite(enablePin, LOW);
  pinMode(enablePin, OUTPUT);
  if(rwPin != -1){
    digitalWrite(rwPin, LOW);
    pinMode(rwPin, OUTPUT);  
  }
  if(backlightPin != -1){
    digitalWrite(backlightPin, LOW);
    pinMode(backlightPin, OUTPUT);  
  }
}

template <unsigned int W, unsigned int H>
void HD44780<W, H>::writeByte(byte b, bool data = true){
  digitalWrite(rsPin, data);
  digitalWrite(enablePin, LOW);
  if(mode_4pin == true){
    
  }
  else{
    
  }
  clock();
}

template <unsigned int W, unsigned int H>
void HD44780<W, H>::clock(void){
  digitalWrite(enablePin, HIGH);
  delayMicroseconds(10);
  digitalWrite(enablePin, LOW);
}

template <unsigned int W, unsigned int H>
void HD44780<W, H>::display(void){
  
}

template <unsigned int W, unsigned int H>
void HD44780<W, H>::clearDisplay(void){
  for(int i = 0; i < W; i++){
    for(int j = 0; j < H; j++){
      bufferA[i][j] = ' ';
      bufferB[i][j] = ' ';
    }
  } 
  activeBuffer = true; 
}

template <unsigned int W, unsigned int H>
void HD44780<W, H>::backlightOn(void){
  if(backlightPin != -1){
    digitalWrite(backlightPin, HIGH);
  }
}

template <unsigned int W, unsigned int H>
void HD44780<W, H>::backlightOff(void){
  if(backlightPin != -1){
    digitalWrite(backlightPin, LOW);
  }
}

template class HD44780<16, 2>;
