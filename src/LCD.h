#ifndef LCD_H
#define LCD_H

#include <LiquidCrystal.h>

#include "config.h"
#include <Arduino.h>

class LCDisplay {
  public:
    LCDisplay();
    void init();
    void clear();
    void blank();
    void print(const char*);
    void printVolume(uint8_t vol);
    void standbyMessage();
    void bootLoader(uint16_t delay);
    LiquidCrystal LCD;
  private:
    void printNumber(uint8_t value, uint8_t col);
    void custom0(uint8_t col);
    void custom1(uint8_t col);
    void custom2(uint8_t col);
    void custom3(uint8_t col);
    void custom4(uint8_t col);
    void custom5(uint8_t col);
    void custom6(uint8_t col);
    void custom7(uint8_t col);
    void custom8(uint8_t col);
    void custom9(uint8_t col);
    void customDash(uint8_t col);
    byte bar1[8] =																	// Create custom characters
    {
      B11100,
      B11110,
      B11110,
      B11110,
      B11110,
      B11110,
      B11110,
      B11100
    };

    byte bar2[8] =
    {
      B00111,
      B01111,
      B01111,
      B01111,
      B01111,
      B01111,
      B01111,
      B00111
    };

    byte bar3[8] =
    {
      B11111,
      B11111,
      B00000,
      B00000,
      B00000,
      B00000,
      B11111,
      B11111
    };

    byte bar4[8] =
    {
      B11110,
      B11100,
      B00000,
      B00000,
      B00000,
      B00000,
      B11000,
      B11100
    };

    byte bar5[8] =
    {
      B01111,
      B00111,
      B00000,
      B00000,
      B00000,
      B00000,
      B00011,
      B00111
    };

    byte bar6[8] =
    {
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B11111,
      B11111
    };

    byte bar7[8] =
    {
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B00111,
      B01111
    };

    byte bar8[8] =
    {
      B11111,
      B11111,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000
    };
};



#endif /* LCD_H */
