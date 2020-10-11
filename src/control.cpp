#include "control.h"

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
