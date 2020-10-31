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
    void init();
    // void setupIrTable();
    void getIRcode();
    void resume();
    boolean RECV_TYPE = true;
    bool valid;
    // int irType = 0;
    uint16_t ircode = 0;
    uint16_t lastIrCode = 0;
};

#endif /* INFRAREDRECEIVER_H */
