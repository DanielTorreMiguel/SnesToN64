#ifndef SNES_CONTROLLER_H
#define SNES_CONTROLLER_H

#define OUT true
#define IN false
#define NUM_BUTTONS 16

#include <stdlib.h>
#include <stdio.h>
#include "pico/stdlib.h"

void snes_controller_init(int latch_pin, int data_pin, int clk_pin);
void snes_get_buttons(uint8_t * buttons);

#endif