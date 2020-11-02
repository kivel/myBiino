#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>
#include <EEPROM.h>

#include "config.h"
#include "settings.h"
#include "LCD.h"
#include "auxBoards.h"

class Input {
  public:
    Input(LCDisplay *lcd1, AuxBoard *a);
    void restore();
    void set();
    void selectInput(uint8_t input);
    void prev();
    void next();
    void printInput();
    uint8_t input;
  private:
    LCDisplay *disp;
    AuxBoard *auxb;
    const char *inputNames[N_INPUTS] = { "moOde DAC ", "2: n/a    ", "3: n/a    ", "4: n/a     ", "5: n/a     ", "Yamaha     " };
};

#endif /* INPUT_H */
