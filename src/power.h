#ifndef POWER_H
#define POWER_H

#include <Arduino.h>
#include <EEPROM.h>

#include "config.h"
#include "LCD.h"

class Power {
  public:
    Power(LCDisplay *lcd);
    void init();
    void restore();
    void on();
    void off();
    void toggle();
    bool state;
  private:
    LCDisplay *disp;
};

#endif /* POWER_H */
