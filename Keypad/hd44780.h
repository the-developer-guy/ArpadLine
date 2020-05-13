/*
 * HD44780 display driver
 * double buffered
 * 
 * 
**/

#include <Arduino.h>

template <unsigned int W, unsigned int H>
class HD44780{
  bool mode_4pin;
  bool activeBuffer;
  char bufferA[W][H];
  char bufferB[W][H];
  int dataPins[8];
  int rsPin;
  int enablePin;
  int rwPin;
  int backlightPin;
  void init(void);
  void initIo(void);
  void clearDisplay(void);
  void writeByte(byte b, bool data = true);
  void clock(void);
public:
  HD44780():
    dataPins{-1, -1, -1, -1, -1, -1, -1, -1},
    activeBuffer(false), rsPin(-1), enablePin(-1), rwPin(-1), backlightPin(-1){}
  HD44780(int enable, int registerSelect, 
          int db7, int db6, int db5, int db4);
  HD44780(int enable, int registerSelect, 
          int db7, int db6, int db5, int db4, int backlight);
  HD44780(int enable, int registerSelect, 
          int db7, int db6, int db5, int db4, int db3, int db2, int db1, int db0);
  HD44780(int enable, int registerSelect, 
          int db7, int db6, int db5, int db4, int db3, int db2, int db1, int db0, int backlight);
  void backlightOn(void);
  void backlightOff(void);
  void display(void);
};
