#ifndef INFRAREDRECEIVER_H
#define INFRAREDRECEIVER_H

#include <IRremote.h>

#include "config.h"

class IRremoteDecoder{
  public:
    IRremoteDecoder();
    IRrecv irrecv;
    decode_results IRrecvResults;
    uint16_t decodeNEC(decode_results * results);
    void initIR();
    void setupIrTable();
    void getIRcode();
    void resume();
    boolean RECV_TYPE = true;
    bool valid;
    // int irType = 0;
    uint16_t ircode = 0;
    uint16_t lastIrCode = 0;
  // private:
    struct irCodes{
      uint16_t Enter;
      uint16_t Up;
      uint16_t Down;
      uint16_t Left;
      uint16_t Right;
      uint16_t Menu;
      uint16_t Play;
      uint16_t Marker;
      uint16_t On;
      uint16_t Off;
      uint16_t Mute;
      uint16_t Inp1;
      uint16_t Inp2;
      uint16_t Inp3;
      uint16_t Inp4;
      uint16_t Inp5;
      uint16_t Inp6;
    } irTable;
};

#endif /* INFRAREDRECEIVER_H */
