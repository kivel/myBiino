#include "LCD.h"

LCDisplay::LCDisplay()
  : LCD(A5, A4, A2, A3, A0, A1)
{}

void LCDisplay::init(){
  LCD.begin(20,2);
  LCD.clear();
  LCD.createChar(1, bar1);
  LCD.createChar(2, bar2);
  LCD.createChar(3, bar3);
  LCD.createChar(4, bar4);
  LCD.createChar(5, bar5);
  LCD.createChar(6, bar6);
  LCD.createChar(7, bar7);
  LCD.createChar(8, bar8);
}

void LCDisplay::clear(){
  LCD.clear();
}

void LCDisplay::print(const char* c){
  LCD.print(c);
}

void LCDisplay::custom0(uint8_t col)															// Create custom numbers
{
  // uses segments to build the number 0
  LCD.setCursor(col, 0);
  LCD.write(2);
  LCD.write(8);
  LCD.write(1);
  LCD.setCursor(col, 1);
  LCD.write(2);
  LCD.write(6);
  LCD.write(1);
}
void LCDisplay::custom1(uint8_t col)
{
  LCD.setCursor(col, 0);
  LCD.write(32);
  LCD.write(32);
  LCD.write(1);
  LCD.setCursor(col, 1);
  LCD.write(32);
  LCD.write(32);
  LCD.write(1);
}
void LCDisplay::custom2(uint8_t col)
{
  LCD.setCursor(col, 0);
  LCD.write(5);
  LCD.write(3);
  LCD.write(1);
  LCD.setCursor(col, 1);
  LCD.write(2);
  LCD.write(6);
  LCD.write(6);
}
void LCDisplay::custom3(uint8_t col)
{
  LCD.setCursor(col, 0);
  LCD.write(5);
  LCD.write(3);
  LCD.write(1);
  LCD.setCursor(col, 1);
  LCD.write(7);
  LCD.write(6);
  LCD.write(1);
}
void LCDisplay::custom4(uint8_t col)
{
  LCD.setCursor(col, 0);
  LCD.write(2);
  LCD.write(6);
  LCD.write(1);
  LCD.setCursor(col, 1);
  LCD.write(32);
  LCD.write(32);
  LCD.write(1);
}
void LCDisplay::custom5(uint8_t col)
{
  LCD.setCursor(col, 0);
  LCD.write(2);
  LCD.write(3);
  LCD.write(4);
  LCD.setCursor(col, 1);
  LCD.write(7);
  LCD.write(6);
  LCD.write(1);
}
void LCDisplay::custom6(uint8_t col)
{
  LCD.setCursor(col, 0);
  LCD.write(2);
  LCD.write(3);
  LCD.write(4);
  LCD.setCursor(col, 1);
  LCD.write(2);
  LCD.write(6);
  LCD.write(1);
}
void LCDisplay::custom7(uint8_t col)
{
  LCD.setCursor(col, 0);
  LCD.write(2);
  LCD.write(8);
  LCD.write(1);
  LCD.setCursor(col, 1);
  LCD.write(32);
  LCD.write(32);
  LCD.write(1);
}
void LCDisplay::custom8(uint8_t col)
{
  LCD.setCursor(col, 0);
  LCD.write(2);
  LCD.write(3);
  LCD.write(1);
  LCD.setCursor(col, 1);
  LCD.write(2);
  LCD.write(6);
  LCD.write(1);
}
void LCDisplay::custom9(uint8_t col)
{
  LCD.setCursor(col, 0);
  LCD.write(2);
  LCD.write(3);
  LCD.write(1);
  LCD.setCursor(col, 1);
  LCD.write(7);
  LCD.write(6);
  LCD.write(1);
}

void LCDisplay::customDash(uint8_t col)
{
  LCD.setCursor(col, 0);
  LCD.write(254);
  LCD.write(6);
  LCD.write(6);
  LCD.setCursor(col, 1);
  LCD.write(254);
  LCD.write(254);
  LCD.write(254);
}

void LCDisplay::printNumber(uint8_t value, uint8_t col){
  if (value == 0) custom0(col);
  if (value == 1) custom1(col);
  if (value == 2) custom2(col);
  if (value == 3) custom3(col);
  if (value == 4) custom4(col);
  if (value == 5) custom5(col);
  if (value == 6) custom6(col);
  if (value == 7) custom7(col);
  if (value == 8) custom8(col);
  if (value == 9) custom9(col);
  if (value == 255) customDash(col);
}

void LCDisplay::printVolume(uint8_t vol){
  if(vol==0){
    LCDisplay::printNumber(255, 12);
    LCDisplay::printNumber(255, 15);
    return;
  }
  uint8_t d, u, number;
  number = vol;
  if (number > 9){
    d = (number - (number % 10)) / 10;
    number = number % 10;
  }
  else{
    d = 0;
  }

  u = number;

  LCDisplay::printNumber(d, 12);
  LCDisplay::printNumber(u, 15);
  LCD.print("dB");
}

void LCDisplay::printPower(bool state){
  clear();
  if(!state){
    LCD.setCursor(5,0);
    LCD.print("power off");
    LCD.setCursor(2,1);
    LCD.print("entering standby");
  }
}

void LCDisplay::bootLoader(uint16_t d){
  LCD.clear();
  LCD.setCursor(2, 0);
  LCD.print("Biino MK3 booting");
  LCD.setCursor(0, 1);
  for(uint8_t i=0; i<20; i++){
    if(i==10){
      LCD.setCursor(2, 0);
      LCD.print("by Dr. K             ");
      LCD.setCursor(9, 1);
    }
    LCD.write(255);
    delay(d/20);
  }
  LCD.clear();
}
