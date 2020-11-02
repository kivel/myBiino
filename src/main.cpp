#include "main.h"

LCDisplay myDisplay;
AuxBoard myAuxBoard;
IRremoteDecoder myIR;
Power myPower(&myDisplay, &myAuxBoard);
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

  /* rotary encoder */
  attachInterrupt(digitalPinToInterrupt(encA),isr, CHANGE);  // ISR for rotary encoder

  /* aux boards */
  myAuxBoard.init();

  /* restore last volume */
  myVolume.restore();

  /* restore last input */
  myInput.restore();
}

void loop() {
  if(myPower.state){
    Crtl.worker();
  } else {
    Crtl.standbyCheck();
    delay(500);
    analogWrite(lcdBacklight, 0);
  }

  delay(150);
}

/*
  interrupt service Subroutine
*/
void isr(){
  if(myPower.state)  Crtl.rotEncoder(digitalRead(encA), digitalRead(encB));
}
