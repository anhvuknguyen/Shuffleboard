#include "Graphics.h"

#include <stdio.h>
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "../inc/ST7735.h"
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../inc/TExaS.h"
#include "../inc/Timer.h"
#include "images/images.h"
#include "Puck.h"


void graphics_init(){
  ST7735_InitPrintf(INITR_BLACKTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
  ST7735_SetRotation(2);
  drawBackground();
}

//Background Functions
int16_t getBackgroundPixel(uint8_t x, uint8_t y) {
  return background[(159-y)*128+x];
}

void drawBackground(){
  for(int i=0;i<128;i++){
    for(int j=0; j<160; j++) {
      ST7735_DrawPixel(i, j, getBackgroundPixel(i, j));
    }
  }
}

void renderPuck(const Puck p){
  if(p.isMoving){
    for(int i=0;i<p.h;i++){
      for(int j=0;j<p.w;j++){
        if(((int8_t)p.oldX+j)<(int8_t)p.x || ((int8_t)p.oldX+j)>((int8_t)p.x+14) || ((int8_t)p.oldY+i)<(int8_t)p.y || ((int8_t)p.oldY+i)>((int8_t)p.y+14))
        ST7735_DrawPixel((int8_t)p.oldX+j, (int8_t)p.oldY+i, getBackgroundPixel((int8_t)p.oldX+j, (int8_t)p.oldY+i));
      }
    }
  }
  for(int i=0;i<p.h;i++){
    for(int j=0;j<p.w;j++){
      if(p.image[i*15 + j]==0x4D84){
        ST7735_DrawPixel((int8_t)p.x+j, (int8_t)p.y+i, getBackgroundPixel((int8_t)p.x+j, (int8_t)p.y+i));
      }else{
        ST7735_DrawPixel((int8_t)p.x+j, (int8_t)p.y+i, p.image[(14-i)*15 + j]);
      }
    }
  }
}