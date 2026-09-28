/* Button.h
 * Rising edge interrupts for PB4 (shoot) and PB1 (reset)
 */
#ifndef __BUTTON_H__
#define __BUTTON_H__

// Button_Init: configure PB4 and PB1 as rising-edge interrupt inputs
// Call after LaunchPad_Init, before __enable_irq
void Button_Init(void);

#endif // __BUTTON_H__
