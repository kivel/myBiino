#include "main.h"

LCDisplay myDisplay;
AuxBoard myAuxBoard;
IRremoteDecoder myIR;
Volume myVolume(&myDisplay, &myAuxBoard);
Control Crtl(&myDisplay, &myVolume, &myIR);
// Control myControls(&myDisplay, &myVolume, &myIR);

uint8_t lastSPIVolume=0;

void setup() {

  arduinoInit();
  /* Start the IR-receiver */
  myIR.initIR();
  // irrecv.enableIRIn();
  myIR.setupIrTable();
  // setupIrTable();

  /* setup LCD */
  myDisplay.init();
  myDisplay.clear();
  // myDisplay.bootLoader(bootDelay);

  /* rotary encoder */
  attachInterrupt(digitalPinToInterrupt(encA),isr, CHANGE);  // ISR for rotary encoder

  myAuxBoard.initSPI();

  /* restore last volume */
  myVolume.restore();
}

int n=0;
int i=0;
void loop() {

  Crtl.checkButtons();
  Crtl.checkIR();

  if(Crtl.factoryReset){
    // resetFactoryDefaults();
    myDisplay.clear();
    myDisplay.print("factory defaults");
    delay(1000);
    resetFunc();  //call reset
    while (true) {
    };
  }

  if(Crtl.buttons.Power){
    myDisplay.clear();
    myDisplay.print("power button");
  }

  if(Crtl.buttons.Enter){
    myDisplay.clear();
    myDisplay.print("Enter");
  }

  Crtl.clearButtons();
  myDisplay.printVolume(Crtl.vol->value);

  delay(150);

}

void isr(){
  Crtl.rotEncoder(digitalRead(encA), digitalRead(encB));
  myDisplay.printVolume(Crtl.vol->value);
}
