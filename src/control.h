#ifndef CONTROL_H
#define CONTROL_H

#include "config.h"
#include "volume.h"
#include "LCD.h"

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
};

struct menuFunctions{
  boolean action = false;
  boolean active = false;
};

class Control{
  long lastDebounceTime = 0;
  public:
    Control(LCDisplay *lcd, Volume *v);
    navButtons buttons;
    menuFunctions menu;
    // Menu menu;
    Volume *vol;
    // Volume vol(Control::&disp);
    bool factoryReset = false;

    void checkButtons();
    void clearButtons();
    void rotEncoder(bool, bool);
    void buttonHandler();
  private:
    LCDisplay *disp;
};

Control::Control(LCDisplay *lcd, Volume *v){
  disp=lcd;
  vol=v;
}

void Control::checkButtons(){
  if ((millis() - lastDebounceTime) > debounceDelay){
    if (digitalRead(resetBtn) == HIGH){
      factoryReset = true;
      lastDebounceTime = millis();
    }

    int readEncoderButton = digitalRead(encC);
    if (readEncoderButton == HIGH)
    {
      buttons.Enter = true;
      // if (Volume == 0)
      // {
      //   button_Enter = true;
      // }
      // else
      // {
      //   button_Channel = true;
      // }
      // if (in_menu == true)(button_Enter = true);
      lastDebounceTime = millis();
    }
  }
}

void Control::clearButtons(){
  buttons.Up = false;
  buttons.Down = false;
  buttons.Left = false;
  buttons.Right = false;
  buttons.Enter = false;
  buttons.Menu = false;
  buttons.Play = false;
  buttons.Channel = false;
  // menu_action = false;
  buttons.Power = false;
}

void Control::rotEncoder(bool enc1, bool enc2){
  if(enc1 == enc2){
    if (menu.active == true){
      buttons.Left = true;
    }
    else{
      buttons.Down = true;
    }
  }
  else{
    if (menu.active == true){
      buttons.Right = true;
    }
    else{
      buttons.Up = true;
    }
  }
  buttonHandler();
}

void Control::buttonHandler(){
  if(buttons.Up)    vol->up();
  if(buttons.Down)  vol->down();
}

#endif /* CONTROL_H */
