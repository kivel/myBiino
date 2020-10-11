#ifndef CONTROL_H
#define CONTROL_H

#include "LCD.h"
#include "volume.h"
#include "infraRedReciever.h"
#include "config.h"

class Control{
  public:
    Control(LCDisplay *lcd, Volume *v, IRremoteDecoder *ir);
    Volume *vol;
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
      boolean Up;
      boolean Down;
      boolean Left;
      boolean Right;
      boolean Enter;
      boolean Menu;
      boolean Play;
      boolean Channel;
      boolean Power;
    } buttons;

    struct menuFunctions{
      boolean action;
      boolean active;
    } menu;

  private:
    long lastDebounceTime;
    LCDisplay *disp;
};



#endif /* CONTROL_H */
