#ifndef __OLED_DRAW_H__
#define __OLED_DRAW_H__

#include <stdint.h>

void OLED_ShowChar(uint8_t x, uint8_t y, char ch, uint8_t Size);
void OLED_ShowText(uint8_t x, uint8_t y, const char *word, uint8_t Size);

extern const uint8_t skull[8];

extern const uint8_t ALPHABET[208];

extern const unsigned char ASCII_0708[95][7];

extern const unsigned char ASCII_1206[95][12];

extern const unsigned char ASCII_1608[95][16];

#endif
