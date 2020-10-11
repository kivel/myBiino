#include "auxBoards.h"

AuxBoard::AuxBoard(){
  initSPI();
}

void AuxBoard::initSPI(){
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
