#include "main.h"

LCDisplay myDisplay;
AuxBoard myAuxBoard;
IRremoteDecoder myIR;
Power myPower(&myDisplay);
Menu myMenu(&myDisplay);
Volume myVolume(&myDisplay, &myAuxBoard);
Input myInput(&myDisplay, &myAuxBoard);
Control Crtl(&myDisplay, &myPower, &myMenu, &myVolume, &myInput, &myIR);

uint8_t lastSPIVolume=0;

void setup() {

  arduinoInit();
  /* Start the IR-receiver */
  myIR.init();

  /* setup LCD */
  myDisplay.init();
  myDisplay.clear();
  // myDisplay.bootLoader(bootDelay);
  myPower.init();

  /* rotary encoder */
  attachInterrupt(digitalPinToInterrupt(encA),isr, CHANGE);  // ISR for rotary encoder

  myAuxBoard.init();

  /* restore last volume */
  myVolume.restore();

  myInput.restore();
}

void loop() {
  if(myPower.state){
    Crtl.worker();
  } else {
    myDisplay.LCD.clear();
    myDisplay.print("standby");
    delay(500);
    myDisplay.LCD.setCursor(0,1);
    myDisplay.print("ENTER for power");
    Crtl.standbyCheck();
    delay(500);
  }

  delay(150);
}

/*
  interrupt service Subroutine
*/
void isr(){
  if(myPower.state)  Crtl.rotEncoder(digitalRead(encA), digitalRead(encB));
}
