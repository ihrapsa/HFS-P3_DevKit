#include "i2c_bitbang.h"

void I2C_Init(void)
{    
    I2C_SDA_HIGH();
    I2C_SCL_HIGH();
}

void I2C_Start(void)
{
    I2C_SDA_HIGH();
    I2C_SCL_HIGH();
    I2C_DELAY();
    I2C_SDA_LOW();
    I2C_DELAY();
    I2C_SCL_LOW();
}

void I2C_Stop(void)
{
    I2C_SDA_LOW();
    I2C_SCL_HIGH();
    I2C_DELAY();
    I2C_SDA_HIGH();
    I2C_DELAY();
}

uint8_t I2C_WriteByte(uint8_t data)
{
    uint8_t i;
    uint8_t ack;

    for (i = 0; i < 8; i++)
    {
        if (data & 0x80)
            I2C_SDA_HIGH();
        else
            I2C_SDA_LOW();
        
        I2C_DELAY();
        I2C_SCL_HIGH();
        I2C_DELAY();
        I2C_SCL_LOW();
        
        data <<= 1;
    }

    I2C_SDA_HIGH();
    I2C_DELAY();
    I2C_SCL_HIGH();
    I2C_DELAY();
    
    ack = I2C_SDA_READ() ? 0 : 1;
    
    I2C_SCL_LOW();
    return ack;
}