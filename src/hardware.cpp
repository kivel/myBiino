#include "hardware.h"

void arduinoInit(){
  pinMode(resetBtn, INPUT);
  pinMode(powerBtn, INPUT);
  pinMode(encA, INPUT);
  pinMode(encB, INPUT);
  pinMode(encC, INPUT);

  pinMode(powerRly, OUTPUT);
  pinMode(chipSelect, OUTPUT);     // Set ChipSelectPin as output

  digitalWrite(chipSelect, HIGH);   // take the CS pin high to de-select the chip:
  digitalWrite(encA, HIGH);
  digitalWrite(encB, HIGH);
  // analogWrite(lcdBacklight, backlightdimming);
  analogWrite(lcdBacklight, 64);

  /* Setup SPI communication */
  pinMode (chipSelect, OUTPUT);     // Set ChipSelectPin as output
  digitalWrite(chipSelect, HIGH);   // take the CS pin high to de-select the chip:
};
