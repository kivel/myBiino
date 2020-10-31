#include "infraRedReciever.h"

IRremoteDecoder::IRremoteDecoder()
  : irrecv(IR_RECEIVE_PIN){
  valid = false;
}

uint16_t IRremoteDecoder::decodeNEC(decode_results * results){
  if (results->decode_type != 11) return 0;
  unsigned long ircode = results->value << 16;
  return ircode >> 16;
}

void IRremoteDecoder::init(){
  irrecv.enableIRIn();
}

void IRremoteDecoder::resume(){
  irrecv.resume();
}

void IRremoteDecoder::getIRcode(){
  valid = false;
  if(irrecv.decode(&IRrecvResults)){
    if(IRrecvResults.isRepeat){
      ircode = lastIrCode;
    }else{
      ircode = decodeNEC(&IRrecvResults);
      lastIrCode = ircode;
      delay(200);
    }
    valid=true;
  }
}
