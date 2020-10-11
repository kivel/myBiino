#include "infraRedReciever.h"

IRremoteDecoder::IRremoteDecoder()
  : irrecv(IR_RECEIVE_PIN)
{
  valid = false;
}

uint16_t IRremoteDecoder::decodeNEC(decode_results * results){
  if (results->decode_type != 11) return 0;
  unsigned long ircode = results->value << 16;
  return ircode >> 16;
}

void IRremoteDecoder::initIR(){
  irrecv.enableIRIn();
}

void IRremoteDecoder::getIRcode(){
  valid = false;
  if(irrecv.decode(&IRrecvResults)){
    if(IRrecvResults.isRepeat){
      ircode = lastIrCode;
    }else{
      ircode = decodeNEC(&IRrecvResults);
      lastIrCode = ircode;
    }
    valid=true;
  }
  irrecv.resume();
}

void IRremoteDecoder::setupIrTable(){
  #if defined(APPLE)
    irTable.Up    = 0xD05C;
    irTable.Down  = 0xB05C;
    irTable.Left  = 0x105C;
    irTable.Right = 0xE05C;
    irTable.Menu  = 0x405C;
    irTable.Play  = 0x205C;
  #endif
  #if defined(MCINTOSH)
    irTable.Enter = 0x38C7;   // OK
    irTable.Up    = 0x42BD;   // Vol +
    irTable.Down  = 0xC23D;   // Vol -
    irTable.Left  = 0xDA25;   // CH -
    irTable.Right = 0x5AA5;   // CH+
    irTable.Menu  = 0x22DD;
    // irTable.Play  = ;
    irTable.On    = 0xD22D;   // PowerOn
    irTable.Off   = 0xFA05;   // PowerOff
    irTable.Mute  = 0x629D;   // Mute
  #endif

  #if defined(PARASOUND)
    irTable.On    = 0x7C83;   // PowerOn
    irTable.Off   = 0x7C03;   // PowerOff
    irTable.Up    = 0x2FD;    // Vol +
    irTable.Down  = 0x827D;   // Vol -
    irTable.Mute  = 0x32CD;   // OK
    irTable.Inp1  = 0x42BD;   //
    irTable.Inp2  = 0xC23D;   //
    irTable.Inp3  = 0x22DD;   //
    irTable.Inp4  = 0xA25D;   //
    irTable.Inp5  = 0x629D;   //
    irTable.Inp6  = 0xE21D;   //
  #endif
}
