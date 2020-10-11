#ifndef CONTROL_H
#define CONTROL_H

#include "config.h"
#include "volume.h"
#include "LCD.h"
#include "infraRedReciever.h"

class Control{
  long lastDebounceTime = 0;
  public:
    Control(LCDisplay *lcd, Volume *v);
    Control(LCDisplay *lcd, Volume *v, IRremoteDecoder *ir);
    Volume *vol;
    IRremoteDecoder *IR;
    bool factoryReset = false;

    void checkButtons();
    void clearButtons();
    void rotEncoder(bool, bool);
    void buttonHandler();
    struct navButtons{
      boolean Up = false;
      boolean Down = false;
      boolean Left = false;
      boolean Right = false;
      boolean Enter = false;
      boolean Menu = false;
      boolean Play = false;
      boolean Channel = false;
      boolean Power = false;
    } buttons;

    struct menuFunctions{
      boolean action = false;
      boolean active = false;
    } menu;
  private:
    LCDisplay *disp;
};



#endif /* CONTROL_H */
