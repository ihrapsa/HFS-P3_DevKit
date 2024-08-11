#include "stdint.h"


#ifndef __BUZZER_H__
#define __BUZZER_H__

void play_beep(void);
void play_tone(uint32_t frequency, uint32_t duration);
void play_melody(void);

#endif

