#include "auxBoards.h"

AuxBoard::AuxBoard(){
  init();
}

void AuxBoard::init(){
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);

  digitalWrite(chipSelect, LOW);         // take the CS pin low to select the chip:
  SPI.transfer(0b01000000);              // Optcode to write to MCP23S17
  SPI.transfer(0x00);                    // Select IODIR register
  SPI.transfer(0x00);                    // Set GPIO as output
  digitalWrite(chipSelect, HIGH);        // take the CS pin high to de-select the chip:

  digitalWrite(chipSelect, LOW);         // take the CS pin low to select the chip:
  SPI.transfer(0b01000000);              // Optcode to write to MCP23S17
  SPI.transfer(IOCON);                   // Select IOCON register
  SPI.transfer(0b00001000);              // Set Hardware Adress Enable
  digitalWrite(chipSelect, HIGH);        // take the CS pin high to de-select the chip:
}

void AuxBoard::change_volume(uint8_t volume){
  digitalWrite(chipSelect, LOW);              // take the CS pin low to select the chip:
  SPI.transfer(0b01000000);          			    // Optcode to write to MCP23S17 #1
  SPI.transfer(GPIO);               				  // Select GPIO register for Volume
  SPI.transfer(0xFF);              					  // Clear Volume
  digitalWrite(chipSelect, HIGH); 					  // take the CS pin high to de-select the chip:

  if (volume > 0){
    delay(5);															    // Anti "pop" delay

    uint8_t volnew = volume ^ 0xFF;  // Bit manipulation to set the correct value
    digitalWrite(chipSelect, LOW);  				  // take the CS pin low to select the chip:
    SPI.transfer(0b01000000);          				// Optcode to write to MCP23S17 #1
    SPI.transfer(GPIO);               				// Select GPIO register for Volume
    SPI.transfer(volnew);           					// Set Volume
    digitalWrite(chipSelect, HIGH);						// take the CS pin high to de-select the chip:
  }
}

void AuxBoard::change_input(uint8_t input){
  digitalWrite(chipSelect, LOW);
  SPI.transfer(0b01000110);
  SPI.transfer(GPIO);
  SPI.transfer(0xFF);
  digitalWrite(chipSelect, HIGH);
  // no input selected, for standby
  if(input==0) return;
  uint8_t spi_input;
  switch (input)
  {
    case (1):
      spi_input = 0xFE;
      break;
    case (2):
      spi_input = 0xFD;
      break;
    case (3):
      spi_input = 0xFB;
      break;
    case (4):
      spi_input = 0xF7;
      break;
    case (5):
      spi_input = 0xEF;
      break;
    case (6):
      spi_input = 0xDF;
      break;
  }

  digitalWrite(chipSelect, LOW);
  SPI.transfer(0b01000110);
  SPI.transfer(GPIO);
  SPI.transfer(spi_input);
  digitalWrite(chipSelect, HIGH);
}
