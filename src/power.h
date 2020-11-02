#ifndef POWER_H
#define POWER_H

#include <Arduino.h>
#include <EEPROM.h>

#include "config.h"
#include "LCD.h"
#include "auxBoards.h"

class Power {
  public:
    Power(LCDisplay *lcd, AuxBoard *a);
    void init();
    void restore();
    void on();
    void off();
    void toggle();
    bool state;
  private:
    LCDisplay *disp;
    AuxBoard *auxb;
    void(* resetFunc) (void) = 0; //declare reset function @ address 0
};

#endif /* POWER_H */
