#include "control.h"

Control::Control(LCDisplay *lcd, Volume *v, Input *i, IRremoteDecoder *ir){
  disp=lcd;       // the display
  vol=v;          // the volume control
  inp=i;          // the input control
  IRdecoder=ir;   // the infra red decoder
  clearButtons();
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
      if(menu.active)   menu.action = !menu.action;
      if(!menu.action)  menu.active = !menu.active;
      lastDebounceTime = millis();
    }
  }
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
  // menu_action = false;
  buttons.Power = false;
}

void Control::rotEncoder(bool enc1, bool enc2){
  if(enc1 == enc2){
    if (menu.active){
      buttons.Left = true;
    } else {
      buttons.Down = true;
    }
  }
  else{
    if (menu.active){
      buttons.Right = true;
    } else {
      buttons.Up = true;
    }
  }
  buttonHandler();
}

void Control::buttonHandler(){
  if(buttons.Up)    vol->up();
  if(buttons.Down)  vol->down();
  if(buttons.Mute)  vol->mute();
  if(!menu.action){
    if(buttons.Left)  inp->prev();
    if(buttons.Right) inp->next();
  }
  clearButtons();
}
