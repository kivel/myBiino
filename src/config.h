#ifndef CONFIG_H
#define CONFIG_H

// #include <EEPROM.h>
#include <Arduino.h>

/* settings for SPI communication */
#define IOCON 0x05 // Control register
#define GPIO 0x09 // InOut register

// EEPROM ADDRESSES
#define INPUT_ID 1
#define INPUT_COUNT 2
#define START_VOLUME 3
#define LAST_VOLUME 4
#define BACKLIGHT_DIMMING 9
#define POWER_RLY_DELAY 30

#define LAST_VOLUME0 40
#define LAST_VOLUME1 41
#define LAST_VOLUME2 42
#define LAST_VOLUME3 43
#define LAST_VOLUME4 44
#define LAST_VOLUME5 45
#define LAST_VOLUME6 46

#define N_INPUTS 6

// IR remote type -->
// #define MCINTOSH
// #define PARASOUND
#define APPLE

// Arduino pins
// inputs
const uint8_t resetBtn = 3;                       // Button to load the settings to the EEPROM
const uint8_t powerBtn = 1;                 // Pin for the Power Button
const uint8_t lcdBacklight = 5;             // Pin for LCD backlight dimming, PWM necessary
const uint8_t encA = 2;                 // Pin for the encoder, must be attached to interrupt
const uint8_t encB = 8;                 // Pin for the second encoder connection
const uint8_t encC = 7;                // Pin for the encoder button
const uint8_t IR_RECEIVE_PIN = 6;                     // Pin for IR receiver input

//outputs
const uint8_t powerRly = 0;                 // Pin for the Biino Power Relais
const uint8_t chipSelect = 4;                   // Pin to select the relais boards

const uint8_t redLED = 9;                   // Pin for the red led
const uint8_t greenLED = 10;                // Pin for the green led

const uint8_t debounceDelay = 250;          // debounceDelay in ms

#if defined(APPLE)
  const uint16_t IR_Up    = 0xD05C;   // +
  const uint16_t IR_Down  = 0xB05C;   // -
  const uint16_t IR_Left  = 0x105C;   // |<<
  const uint16_t IR_Right = 0xE05C;   // >>|
  const uint16_t IR_Play  = 0x405C;   // Menu
  const uint16_t IR_Mute  = 0x205C;   // Play
#endif

#if defined(PARASOUND)
  const uint16_t IR_On    = 0x7C83;   // PowerOn
  const uint16_t IR_Off   = 0x7C03;   // PowerOff
  const uint16_t IR_Up    = 0x2FD;    // Vol +
  const uint16_t IR_Down  = 0x827D;   // Vol -
  const uint16_t IR_Mute  = 0x32CD;   // OK
  const uint16_t IR_Inp1  = 0x42BD;   //
  const uint16_t IR_Inp2  = 0xC23D;   //
  const uint16_t IR_Inp3  = 0x22DD;   //
  const uint16_t IR_Inp4  = 0xA25D;   //
  const uint16_t IR_Inp5  = 0x629D;   //
  const uint16_t IR_Inp6  = 0xE21D;   //
#endif

// void resetFactoryDefaults(){
//   EEPROM.write (INPUT_ID,           1); 		// Start Input
//   EEPROM.write (INPUT_COUNT,        6); 		// Number of Inputs
//   EEPROM.write (START_VOLUME,       10); 		// Start Volume
//   EEPROM.write (LAST_VOLUME,        10);    // Last Volume
//   EEPROM.write (BACKLIGHT_DIMMING,  255); 	// Backlight dimming
//   // EEPROM.write (10, 0x3A);  	// Enter
//   // EEPROM.write (11, 0x50);  	// Up
//   // EEPROM.write (12, 0x30);  	// Down
//   // EEPROM.write (13, 0x10);  	// Left
//   // EEPROM.write (14, 0x60);  	// Right
//   // EEPROM.write (15, 0x40);  	// Menu
//   // EEPROM.write (16, 0x7A);  	// Play
//   // EEPROM.write (17, 0x01);  	// Marker for Apple Remote
//   // EEPROM.write (POWER_RLY_DELAY,    0); 		  // Power Relay Delay
//   // EEPROM.write (31,  0); 		  // Att. board 2
//   // EEPROM.write (32,  0); 		  // Att. board 3
//   // EEPROM.write (33,  0); 		  // Att. board 4
//   // EEPROM.write (34,  0); 		  // max. attenuation
//
//   EEPROM.write (LAST_VOLUME1,        0);    // Last Volume
//   EEPROM.write (LAST_VOLUME2,        0);    // Last Volume
//   EEPROM.write (LAST_VOLUME3,        0);    // Last Volume
//   EEPROM.write (LAST_VOLUME4,        0);    // Last Volume
//   EEPROM.write (LAST_VOLUME5,        0);    // Last Volume
//   EEPROM.write (LAST_VOLUME6,        0);    // Last Volume
//
//   // EEPROM.write (100,   73);	// I
//   // EEPROM.write (101,   78);	// N
//   // EEPROM.write (102,   80);	// P
//   // EEPROM.write (103,   85);	// U
//   // EEPROM.write (104,   84);	// T
//   // EEPROM.write (105,   32);	// 	blank
//   // EEPROM.write (106,   49);	// 1
//   // EEPROM.write (107,   32);	//	blank
//   // EEPROM.write (108,   32);	//	blank
//   // EEPROM.write (109,   32);	//	blank
//   // EEPROM.write (110,   32);	//  blank
//   // EEPROM.write (111,   32);	//	blank
//   //
//   // EEPROM.write (120,   73);	// I
//   // EEPROM.write (121,   78);	// N
//   // EEPROM.write (122,   80);	// P
//   // EEPROM.write (123,   85);	// U
//   // EEPROM.write (124,   84);	// T
//   // EEPROM.write (125,   32);	// 	blank
//   // EEPROM.write (126,   50);	// 2
//   // EEPROM.write (127,   32);	//	blank
//   // EEPROM.write (128,   32);	//	blank
//   // EEPROM.write (129,   32);	//	blank
//   // EEPROM.write (130,   32);	//  blank
//   // EEPROM.write (131,   32);	//	blank
//   //
//   // EEPROM.write (140,   73);	// I
//   // EEPROM.write (141,   78);	// N
//   // EEPROM.write (142,   80);	// P
//   // EEPROM.write (143,   85);	// U
//   // EEPROM.write (144,   84);	// T
//   // EEPROM.write (145,   32);	// 	blank
//   // EEPROM.write (146,   51);	// 3
//   // EEPROM.write (147,   32);	//	blank
//   // EEPROM.write (148,   32);	//	blank
//   // EEPROM.write (149,   32);	//	blank
//   // EEPROM.write (150,   32);	//  blank
//   // EEPROM.write (151,   32);	//	blank
//   //
//   // EEPROM.write (160,   73);	// I
//   // EEPROM.write (161,   78);	// N
//   // EEPROM.write (162,   80);	// P
//   // EEPROM.write (163,   85);	// U
//   // EEPROM.write (164,   84);	// T
//   // EEPROM.write (165,   32);	// 	blank
//   // EEPROM.write (166,   52);	// 4
//   // EEPROM.write (167,   32);	//	blank
//   // EEPROM.write (168,   32);	//	blank
//   // EEPROM.write (169,   32);	//	blank
//   // EEPROM.write (170,   32);	//  blank
//   // EEPROM.write (171,   32);	//	blank
//   //
//   // EEPROM.write (180,   73);	// I
//   // EEPROM.write (181,   78);	// N
//   // EEPROM.write (182,   80);	// P
//   // EEPROM.write (183,   85);	// U
//   // EEPROM.write (184,   84);	// T
//   // EEPROM.write (185,   32);	// 	blank
//   // EEPROM.write (186,   53);	// 5
//   // EEPROM.write (187,   32);	//	blank
//   // EEPROM.write (188,   32);	//	blank
//   // EEPROM.write (189,   32);	//	blank
//   // EEPROM.write (190,   32);	//  blank
//   // EEPROM.write (191,   32);	//	blank
//   //
//   // EEPROM.write (200,   73);	// I
//   // EEPROM.write (201,   78);	// N
//   // EEPROM.write (202,   80);	// P
//   // EEPROM.write (203,   85);	// U
//   // EEPROM.write (204,   84);	// T
//   // EEPROM.write (205,   32);	// 	blank
//   // EEPROM.write (206,   54);	// 6
//   // EEPROM.write (207,   32);	//	blank
//   // EEPROM.write (208,   32);	//	blank
//   // EEPROM.write (209,   32);	//	blank
//   // EEPROM.write (210,   32);	//  blank
//   // EEPROM.write (211,   32);	//	blank
// }

#endif /* CONFIG_H */
