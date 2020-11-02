#include "power.h"

Power::Power(LCDisplay *lcd, AuxBoard *a){
  disp=lcd;
  auxb=a;
  state = false;
}

void Power::on(){
  resetFunc();
}

void Power::off(){
  state=0;
  auxb->change_input(0);
  auxb->change_volume(0);
  disp->standbyMessage();
}
