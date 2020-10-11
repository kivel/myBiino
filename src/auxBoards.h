#ifndef AUXBOARDS_H
#define AUXBOARDS_H

#include <SPI.h>
#include <Arduino.h>

#include "config.h"

class AuxBoard {
  public:
    AuxBoard();
    void initSPI();
    void change_volume(uint8_t volume);
};

#endif /* AUXBOARDS_H */
