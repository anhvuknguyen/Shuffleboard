/* Button.c
 * Rising edge interrupts for PB4 (shoot) and PB1 (reset)
 * Hardware debouncing already handled externally
 */
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"

volatile uint32_t ShootFlag;  // 1 on rising edge of PB4
volatile uint32_t ResetFlag;  // 1 on rising edge of PB1

void Button_Init(void){
  IOMUX->SECCFG.PINCM[PB4INDEX] = 0x00040081;            
  IOMUX->SECCFG.PINCM[PB1INDEX] = 0x00040081;         
  GPIOB->POLARITY15_0 = (1<<(4<<1))|(1<<(1<<1));         
  GPIOB->CPU_INT.ICLR  = (1<<4)|(1<<1);                   
  GPIOB->CPU_INT.IMASK = (1<<4)|(1<<1);                
  NVIC->IP[0] = (NVIC->IP[0]&(~0x0000FF00))|2<<14;       
  NVIC->ISER[0] = 1<<1;                              
}

void GROUP1_IRQHandler(void){
  if(GPIOB->CPU_INT.RIS & (1<<4)){  // PB4 shoot
    ShootFlag = 1;
    GPIOB->CPU_INT.ICLR = 1<<4;
  }
  if(GPIOB->CPU_INT.RIS & (1<<1)){  // PB1 reset
    ResetFlag = 1;
    GPIOB->CPU_INT.ICLR = 1<<1;
  }
}
