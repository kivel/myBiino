#include "volume.h"

Volume::Volume(LCDisplay *lcd, AuxBoard *a){
  disp=lcd;
  auxb=a;
}

void Volume::mute(){
  if(!muteOn){            // if not muted
    muteOn = true;        // set mute flag
    muteValue = value;    // store current value
    value = 0;            // set volume value to ZERO
  }else{                  // if muted
    Volume::unMute();     // call unmute
  }
  set();
}

void Volume::unMute(){
  muteOn = false;
  value = muteValue;
};

void Volume::restore(){
  value = EEPROM.read(START_VOLUME);
  set();
}

void Volume::restore(uint8_t input){
  if(input<1 || input>EEPROM.read(INPUT_COUNT)){
    mute();
    exit(0);
  }
  value = EEPROM.read(LAST_VOLUME0+input);
}

void Volume::up(){
  if(muteOn){
    unMute();
  }
  if(value<64) value++;  //prevent overflow
  set();
}

void Volume::down(){
  if(muteOn){
    unMute();
  }
  if(value>0) value--;  //prevent underflow
  set();
}

void Volume::set(){
  if(value==0){
    auxb->change_volume(value);
  }else if((value-oldValue)>1){
    // ramp
    while(oldValue<value){
      oldValue++;
      disp->printVolume(oldValue);
      auxb->change_volume(value);
      delay(50);
    }
  }else{
    auxb->change_volume(value);
  }
  oldValue = value;
  EEPROM.write(START_VOLUME, value);
}
