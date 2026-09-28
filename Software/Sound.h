// Sound.h
// 12-bit DAC sound output on PA15
// Rishi Bala, Anh-Vu Nguyen
#ifndef SOUND_H
#define SOUND_H
#include <stdint.h>

// Initialize 12-bit DAC and SysTick at 11025 Hz; no sound plays until Sound_Start
void Sound_Init(void);

// Set active sound buffer and re-enable output; plays once then stops
// pt    - pointer to array of 8-bit PCM samples (0-255)
// count - number of samples
void Sound_Start(const uint8_t *pt, uint32_t count);

void Sound_Shoot(void);     // puck firing sound
void Sound_Collision(void); // puck/wall collision sound
void Sound_Winner(void);    // winner sound

#endif
