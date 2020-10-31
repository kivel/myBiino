#include "main.h"

LCDisplay myDisplay;
AuxBoard myAuxBoard;
IRremoteDecoder myIR;
Volume myVolume(&myDisplay, &myAuxBoard);
Input myInput(&myDisplay, &myAuxBoard);
Control Crtl(&myDisplay, &myVolume, &myInput, &myIR);
// Control myControls(&myDisplay, &myVolume, &myIR);

uint8_t lastSPIVolume=0;

void setup() {

  arduinoInit();
  /* Start the IR-receiver */
  myIR.init();

  /* setup LCD */
  myDisplay.init();
  myDisplay.clear();
  // myDisplay.bootLoader(bootDelay);

  /* rotary encoder */
  attachInterrupt(digitalPinToInterrupt(encA),isr, CHANGE);  // ISR for rotary encoder

  myAuxBoard.init();

  /* restore last volume */
  myVolume.restore();

  myInput.restore();
}

void loop() {
  Crtl.checkButtons();
  Crtl.checkIR();
  delay(150);
}

void isr(){
  Crtl.rotEncoder(digitalRead(encA), digitalRead(encB));
}
