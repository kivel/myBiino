#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

#include "control.h"
#include "hardware.h"
#include "config.h"
#include "power.h"
#include "menu.h"
#include "volume.h"
#include "input.h"
#include "auxBoards.h"

// void(* resetFunc) (void) = 0; //declare reset function @ address 0

void isr();

#endif /* MAIN_H */
