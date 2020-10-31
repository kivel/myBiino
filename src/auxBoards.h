#ifndef AUXBOARDS_H
#define AUXBOARDS_H

#include <SPI.h>
#include <Arduino.h>

#include "config.h"

class AuxBoard {
  public:
    AuxBoard();
    void init();
    void change_volume(uint8_t volume);
    void change_input(uint8_t input);
  private:
    uint8_t spi_input = 0xFE;
};

#endif /* AUXBOARDS_H */
