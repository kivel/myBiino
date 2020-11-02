#include "power.h"

Power::Power(LCDisplay *lcd, AuxBoard *a){
  disp=lcd;
  auxb=a;
  state = false;
}

void Power::init(){
  restore();
}

void Power::restore(){
  state = EEPROM.read(POWER_STATE);
  disp->printPower(state);
}

void Power::on(){
  resetFunc();
}

void Power::off(){
  state=0;
  auxb->change_input(0);
  auxb->change_volume(0);
  disp->clear();
  disp->print("power off");
  delay(1000);
}

void Power::toggle(){}
