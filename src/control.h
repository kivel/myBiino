#ifndef CONTROL_H
#define CONTROL_H

#include "LCD.h"
#include "volume.h"
#include "input.h"
#include "infraRedReciever.h"
#include "config.h"

class Control{
  public:
    Control(LCDisplay *lcd, Volume *v, Input *i, IRremoteDecoder *ir);
    Volume *vol;
    Input *inp;
    IRremoteDecoder *IRdecoder;

    bool factoryReset;
    uint8_t input;

    void checkButtons();
    void clearButtons();
    void checkIR();
    void rotEncoder(bool, bool);
    void buttonHandler();
    void printCode();

    struct navButtons{
      bool Up;
      bool Down;
      bool Mute;
      bool Left;
      bool Right;
      bool Enter;
      bool Menu;
      bool Play;
      bool Channel;
      bool Power;
    } buttons;

    struct menuFunctions{
      bool action;
      bool active;
    } menu;

  private:
    long lastDebounceTime;
    LCDisplay *disp;
    void(* resetFunc) (void) = 0; //declare reset function @ address 0
};



#endif /* CONTROL_H */
