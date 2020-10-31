#include "input.h"
#include "config.h"

Input::Input(LCDisplay *lcd1, AuxBoard *a){
  disp=lcd1;
  auxb=a;
  spi_input = 0xFF;
  input = 0;
}

void Input::set(){
  auxb->change_input(input);
  printInput();
  EEPROM.write(INPUT_ID, input);
}

void Input::selectInput(uint8_t i){
  input = i;
  set();
}

void Input::restore(){
  input = EEPROM.read(INPUT_ID);
  set();
}

void Input::prev(){
  if(input>1) input--;
  set();
}

void Input::next(){
  if(input<N_INPUTS) input++;
  set();
}

void Input::printInput(){
  disp->LCD.setCursor(0,0);
  disp->print(inputNames[input-1]);
}
