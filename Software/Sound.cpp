// Sound.cpp
// Runs on MSPM0G3507
// 12-bit DAC sound output on PA15 at 11025 Hz via SysTick
// Rishi Bala, Anh-Vu Nguyen
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "Sound.h"
#include "shoot.txt"
#include "collision.txt"
#include "winner.txt"
#include "../inc/DAC5.h"

static const uint16_t *SoundPtr = 0;
static const uint16_t *SoundEnd = 0;

void Sound_Init(void){
  DAC5_Init();
  SoundPtr = 0;
  SoundEnd = 0;
  SysTick->CTRL = 0;
  SysTick->LOAD = (80000000/11025) - 1;
  SysTick->VAL  = 0;
  SCB->SHP[1] = (SCB->SHP[1] & ~0xC0000000) | (2U << 30);
  SysTick->CTRL = 0x00000007;
}

extern "C" void SysTick_Handler(void);
void SysTick_Handler(void){
  if(SoundPtr >= SoundEnd){
    DAC5_Out(2048);
    return;
  }
  DAC5_Out((uint32_t)(*SoundPtr) << 4);
  SoundPtr++;
}

void Sound_Start(const uint16_t *pt, uint32_t count){
  SoundPtr = pt;
  SoundEnd = pt + count;
}

void Sound_Shoot(void){
  Sound_Start(shoot, sizeof(shoot)/sizeof(shoot[0]));
}

void Sound_Collision(void){
  Sound_Start(collision, sizeof(collision)/sizeof(collision[0]));
}

void Sound_Winner(void){
  Sound_Start(winner, sizeof(winner)/sizeof(winner[0]));
}
