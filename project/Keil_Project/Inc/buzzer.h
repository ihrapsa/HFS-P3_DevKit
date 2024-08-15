#include "stdint.h"


#ifndef __BUZZER_H__
#define __BUZZER_H__

void play_beep(void);
void play_click(void);
void play_click_1ms(void);
void play_click_500us(void);
void play_tone(uint32_t frequency, uint32_t duration);
void play_melody(void);
//void simulate_radioactive_decay(double half_life_seconds, double duration_seconds, int initial_atoms);

#endif

