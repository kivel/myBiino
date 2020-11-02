#include "control.h"

Control::Control(LCDisplay *lcd, Power *p, Menu *m, Volume *v, Input *i, IRremoteDecoder *ir){
  disp=lcd;       // the display
  pwr=p;
  menu=m;
  vol=v;          // the volume control
  inp=i;          // the input control
  IRdecoder=ir;   // the infra red decoder
  // standby = EEPROM.read(POWER_STATE);
  clearButtons();
}

void Control::worker(){
  checkButtons();
  checkIR();
  menuAutoExit();
}

void Control::standbyCheck(){
  if(digitalRead(encC)){
    pwr->on();
    menuExit();
  }
}

/*
  this handles the human input via physical buttons
*/
void Control::checkButtons(){
  if ((millis() - lastDebounceTime) > debounceDelay){

    if (digitalRead(resetBtn) == HIGH){
      disp->clear();
      disp->print("     reset");
      delay(200);
      resetFunc();  //call reset
      lastDebounceTime = millis();
    }

    int readEncoderButton = digitalRead(encC);
    if (readEncoderButton == HIGH){
      menu->enter();
      buttonHandler();
      lastDebounceTime = millis();
    }
  }
}

/*
  this handles human input via irreceiver
*/
void Control::checkIR(){
  IRdecoder->getIRcode(); // get whatever is in the pipeline
  if(IRdecoder->valid){   // only process if flagged valid
    switch (IRdecoder->ircode) {
      case IR_Up:     buttons.Up    = true; break;
      case IR_Down:   buttons.Down  = true; break;
      case IR_Left:   buttons.Left  = true; break;
      case IR_Right:  buttons.Right = true; break;
      case IR_Mute:   buttons.Mute  = true; break;
      case IR_Play:   buttons.Play  = true; break;
      case IR_On:     buttons.PowerOn = true; break;
      case IR_Off:    buttons.PowerOff = true; break;
      default:  disp->clear();
                disp->LCD.print("unknown IR code");
                disp->LCD.setCursor(0, 1);
                disp->LCD.print("0x");
                disp->LCD.print(IRdecoder->ircode, HEX);
                break;
    }
    IRdecoder->resume();  // resume IR receiver
    buttonHandler();      // call worker function
  };
}

void Control::clearButtons(){
  buttons.Up = false;
  buttons.Down = false;
  buttons.Mute = false;
  buttons.Left = false;
  buttons.Right = false;
  buttons.Enter = false;
  buttons.Menu = false;
  buttons.Play = false;
  buttons.Channel = false;
  buttons.Power = false;
  buttons.PowerOn = false;
  buttons.PowerOff = false;
}

void Control::menuExit(){
  disp->clear();
  disp->printVolume(vol->value);
  inp->printInput();
  menu->init();
}

void Control::menuAutoExit(){
  if ((millis() - lastButtonTime) > 5000){
    menuExit();
  }
}

void Control::rotEncoder(bool enc1, bool enc2){
  if(enc1 == enc2){
    if (menu->mainMenu>0){
      buttons.Left = true;
    } else {
      buttons.Down = true;
    }
  }
  else{
    if (menu->mainMenu>0){
      buttons.Right = true;
    } else {
      buttons.Up = true;
    }
  }
  buttonHandler();
}

void Control::buttonHandler(){
  if(buttons.Mute)  vol->mute();
  switch (menu->mainMenu) {
    case Menu::volume:
      if(buttons.Up)    vol->up();
      if(buttons.Down)  vol->down();
    case Menu::inputs:
      if(buttons.Left)  inp->prev();
      if(buttons.Right) inp->next();
      break;
    case Menu::power:
      if(buttons.Left)  menu->prev();
      if(buttons.Right) menu->next();
      if(menu->action && menu->pwrMenu==1){
        pwr->off();
        menu->init();
        break;
      }
      if(menu->action && menu->pwrMenu==0){
        menuExit();
      }
  }
  lastButtonTime = millis();
  clearButtons();
}
