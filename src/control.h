#ifndef CONTROL_H
#define CONTROL_H

#include "LCD.h"
#include "volume.h"
#include "input.h"
#include "infraRedReciever.h"
#include "config.h"
#include "power.h"
#include "menu.h"

class Control{
  public:
    Control(LCDisplay *lcd, Power *p, Menu *m, Volume *v, Input *i, IRremoteDecoder *ir);

    void worker();
    void standbyCheck();
    void rotEncoder(bool, bool);

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
      bool PowerOn;
      bool PowerOff;
    } buttons;

  private:
    Volume *vol;
    Input *inp;
    IRremoteDecoder *IRdecoder;
    Power *pwr;
    Menu *menu;
    LCDisplay *disp;
    long lastDebounceTime;
    long lastButtonTime;
    void checkButtons();
    void checkIR();
    void menuExit();
    void menuAutoExit();
    void clearButtons();
    void buttonHandler();
    void standbyHandler();
    void(* resetFunc) (void) = 0; //declare reset function @ address 0
};



#endif /* CONTROL_H */
