#include "main.h"
#include "fm33_assert.h"
#include "fm33lc0xx_fl_gpio.h"

#ifndef __I2C_BITBANG_H__
#define __I2C_BITANG_H__


#define I2C_SDA_PIN     FL_GPIO_PIN_0
#define I2C_SCL_PIN     FL_GPIO_PIN_1
#define I2C_GPIO        GPIOD

#define I2C_SDA_HIGH()  FL_GPIO_SetOutputPin(I2C_GPIO, I2C_SDA_PIN)
#define I2C_SDA_LOW()   FL_GPIO_ResetOutputPin(I2C_GPIO, I2C_SDA_PIN)
#define I2C_SCL_HIGH()  FL_GPIO_SetOutputPin(I2C_GPIO, I2C_SCL_PIN)
#define I2C_SCL_LOW()   FL_GPIO_ResetOutputPin(I2C_GPIO, I2C_SCL_PIN)
#define I2C_SDA_READ()  FL_GPIO_GetInputPin(I2C_GPIO, I2C_SDA_PIN)

#define I2C_DELAY()     FL_DelayUs(5)  // Adjust delay as needed

void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
uint8_t I2C_WriteByte(uint8_t data);


#endif // I2C_BITBANG_H