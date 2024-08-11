#ifndef __OLED_I2C_H__
#define __OLED_I2C_H__

#include "fm33lc0xx_fl_gpio.h"

void OLED_WriteCommand(uint8_t cmd);
void OLED_WriteData(uint8_t data);
void OLED_WriteDataList(const uint8_t *list, uint8_t length);

void OLED_Init(void);
void OLED_Init2(void);

//void OLED_FillScreen(uint8_t pattern);
//void OLED_TestPattern(void);
void OLED_HardwareReset(void);

void OLED_SetPosition(uint8_t x, uint8_t y);
void OLED_Clear(void);

void OLED_StartPosition(void);

#endif // __OLED_I2C_H__