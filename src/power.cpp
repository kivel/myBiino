#include "power.h"

Power::Power(LCDisplay *lcd){
  disp=lcd;
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
  state=1;
  // disp->printPower(state);
}

void Power::off(){
  state=0;
  disp->clear();
  disp->print("power off");
  delay(1000);
}

void Power::toggle(){}
