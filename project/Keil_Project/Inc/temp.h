
#ifndef __TEMP_H__
#define __TEMP_H__

#include "fm33lc0xx_fl.h"

#define TS_CAL1       (*((uint16_t *)(0x1FFFFa92)))   // 30*C PTAT sampling value
extern float GetTS_POLL(void);

#endif // __TEMP_H__