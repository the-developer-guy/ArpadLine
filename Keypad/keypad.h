#include <Arduino.h>
/**
 * Keypad driver
 * for writing stuff
 * 
 * Single pushed button only by design,
 * multiple pushed buttons are invalid.
 */

#define KEYPAD_INVALID -1
#define KEYPAD_NONE 0

enum KeypadType{
  Keypad_4_3 = 3,
  Keypad_4_4 = 4  
};

class Keypad{
  static const PROGMEM char keymap[4][4] = {
    '1', '2', '3', 'A',
    '4', '5', '6', 'B',
    '7', '8', '9', 'C',
    '*', '0', '#', 'D'
  };
  KeypadType type;
  int row[4];
  int column[4];
  bool addressLine(unsigned int  line);
  char presseddButton(void);
  void initIo(void);
 public:
  Keypad();
  Keypad(int row_1, int row_2, int row_3, int row_4, 
         int column_1, int column_2, int column_3, int column_4);
  Keypad(int row_1, int row_2, int row_3, int row_4, 
         int column_1, int column_2, int column_3);
};
