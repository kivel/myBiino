#ifndef VOLUME_H
#define VOLUME_H

#include <Arduino.h>
#include <EEPROM.h>

#include "config.h"
#include "settings.h"
#include "LCD.h"
#include "auxBoards.h"

class Volume {
  public:
    Volume(LCDisplay *lcd1, AuxBoard *a);
    bool muteOn = false;
    uint8_t value;
    void mute();
    void unMute();
    void restore();
    void restore(uint8_t input);
    void up();
    void down();
    void set();
  private:
    LCDisplay *disp;
    AuxBoard *auxb;
    uint8_t oldValue = 0;
    uint8_t muteValue = 0;
};



#endif /* VOLUME_H */
