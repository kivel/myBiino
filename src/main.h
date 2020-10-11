#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <SPI.h>
#include <LiquidCrystal.h>

#include "hardware.h"
#include "config.h"
#include "settings.h"
#include "control.h"
#include "LCD.h"
#include "infraRedReciever.h"
#include "volume.h"
#include "auxBoards.h"

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void printVol();

void isr();

#endif /* MAIN_H */
