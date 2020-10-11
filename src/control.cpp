#include "control.h"

Control::Control(LCDisplay *lcd, Volume *v, IRremoteDecoder *ir){
  disp=lcd;
  vol=v;
  IRdecoder=ir;
  clearButtons();
  factoryReset=false;
}

void Control::checkIR(){
  int i;
  i=0;
  IRdecoder->getIRcode(); // get whatever is in the pipeline
  if(IRdecoder->valid){   // only process if flagged valid
    if(IRdecoder->ircode == IRdecoder->irTable.Up)    vol->up();
    if(IRdecoder->ircode == IRdecoder->irTable.Down)  vol->down();
    if(IRdecoder->ircode == IRdecoder->irTable.Mute)  vol->mute();
    #if defined(APPLE)
      if(IRdecoder->ircode == IRdecoder->irTable.Menu)  vol->mute();
    #endif
    if(IRdecoder->ircode == IRdecoder->irTable.On)    buttons.Power=true;
    if(IRdecoder->ircode == IRdecoder->irTable.Enter) buttons.Enter=true;
    if(IRdecoder->ircode == IRdecoder->irTable.Inp1) i=1;
    if(IRdecoder->ircode == IRdecoder->irTable.Inp2) i=2;
    if(IRdecoder->ircode == IRdecoder->irTable.Inp3) i=3;
    if(IRdecoder->ircode == IRdecoder->irTable.Inp4) i=4;
    if(IRdecoder->ircode == IRdecoder->irTable.Inp5) i=5;
    if(IRdecoder->ircode == IRdecoder->irTable.Inp6) i=6;
  };
  IRdecoder->resume();  // resume IR receiver
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
