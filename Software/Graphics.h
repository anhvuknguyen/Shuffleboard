#ifndef __Graphics_h
#define __Graphics_h

#include <stdio.h>
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "../inc/ST7735.h"
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../inc/TExaS.h"
#include "../inc/Timer.h"
#include "Puck.h"
#include "images/images.h"


void graphics_init();
int16_t getBackgroundPixel(uint8_t x, uint8_t y);
void drawBackground();
void renderPuck(const Puck p);
#endif
