#include "main.h"

#include <SPI.h>

LCDisplay myDisplay;
AuxBoard myAuxBoard;
IRremoteDecoder myIR;
Volume myVolume(&myDisplay, &myAuxBoard);
Control Crtl(&myDisplay, &myVolume);

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
  // IR test

  myIR.getIRcode();
  if(myIR.valid){
    if(myIR.ircode == myIR.irTable.Up)    Crtl.vol->up();
    if(myIR.ircode == myIR.irTable.Down)  Crtl.vol->down();
    if(myIR.ircode == myIR.irTable.Mute)  Crtl.vol->mute();
    #if defined(APPLE)
      if(myIR.ircode == myIR.irTable.Menu)  Crtl.vol->mute();
    #endif
    if(myIR.ircode == myIR.irTable.On)    Crtl.buttons.Power=true;
    if(myIR.ircode == myIR.irTable.Enter) Crtl.buttons.Enter=true;
    if(myIR.ircode == myIR.irTable.Inp1) i=1;
    if(myIR.ircode == myIR.irTable.Inp2) i=2;
    if(myIR.ircode == myIR.irTable.Inp3) i=3;
    if(myIR.ircode == myIR.irTable.Inp4) i=4;
    if(myIR.ircode == myIR.irTable.Inp5) i=5;
    if(myIR.ircode == myIR.irTable.Inp6) i=6;

  };

  Crtl.checkButtons();

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
