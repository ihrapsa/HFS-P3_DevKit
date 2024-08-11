#include "i2c_bitbang.h"

#define OLED_ADDRESS 0x3C  // Typical address for SSD1316, might be different
#define OLED_RESET_PIN FL_GPIO_PIN_13  
#define OLED_RESET_PORT GPIOA

void OLED_HardwareReset(void)
{
    // Perform reset sequence
    FL_GPIO_SetOutputPin(OLED_RESET_PORT, OLED_RESET_PIN);
    FL_DelayMs(10);
    FL_GPIO_ResetOutputPin(OLED_RESET_PORT, OLED_RESET_PIN);
    FL_DelayMs(10);
    FL_GPIO_SetOutputPin(OLED_RESET_PORT, OLED_RESET_PIN);
    FL_DelayMs(100);  // Wait for the reset to complete
}


void OLED_WriteCommand(uint8_t cmd)
{
    I2C_Start();
    I2C_WriteByte(OLED_ADDRESS << 1);
    I2C_WriteByte(0x00);  // Command mode
    I2C_WriteByte(cmd);
    I2C_Stop();
}

void OLED_WriteData(uint8_t data)
{
    I2C_Start();
    I2C_WriteByte(OLED_ADDRESS << 1);
    I2C_WriteByte(0x40);  // Data mode
    I2C_WriteByte(data);
    I2C_Stop();
}

void OLED_WriteDataList(const uint8_t *list, uint8_t length)
{
		I2C_Start();
    I2C_WriteByte(OLED_ADDRESS << 1);
    I2C_WriteByte(0x40);  // Data mode
		for (uint8_t i = 0; i < length; i++)
		{
				I2C_WriteByte(list[i]);
		}
		I2C_Stop();
}
	


void OLED_Init(void)	
{
    // Now send initialization commands
    OLED_WriteCommand(0xAE);  // Display off
    OLED_WriteCommand(0xD5);  // Set display clock divide ratio/oscillator frequency
    OLED_WriteCommand(0x80);  // Set divide ratio
    OLED_WriteCommand(0xA8);  // Set multiplex ratio
    OLED_WriteCommand(0x27);  // 1/39 duty (for 128x39 display mode)
    OLED_WriteCommand(0xD3);  // Set display offset
    OLED_WriteCommand(0x00);  // No offset
    OLED_WriteCommand(0x40);  // Set display start line to 0
    OLED_WriteCommand(0x8D);  // Set charge pump
    OLED_WriteCommand(0x14);  // Enable charge pump
    OLED_WriteCommand(0x20);  // Set memory addressing mode
    OLED_WriteCommand(0x10);  // 00 Horizontal addressing mode  10 Vertical
    OLED_WriteCommand(0xA1);  // Set segment re-map (A0 or A1)
    OLED_WriteCommand(0xC0);  // Set COM output scan direction (C0 or C8)
    OLED_WriteCommand(0xDA);  // Set COM pins hardware configuration
    OLED_WriteCommand(0x12);  // Alternative COM pin configuration
    OLED_WriteCommand(0x81);  // Set contrast control
    OLED_WriteCommand(0x7F);  // Set contrast to midpoint
    OLED_WriteCommand(0xD9);  // Set pre-charge period
    OLED_WriteCommand(0xF1);  // Phase 1 = 15, Phase 2 = 1
    OLED_WriteCommand(0xDB);  // Set VCOMH deselect level
    OLED_WriteCommand(0x40);  // VCOMH deselect level ~ 0.81 x VCC
    OLED_WriteCommand(0xA4);  // Entire display ON, resume to RAM content display
    OLED_WriteCommand(0xA6);  // Set normal display
    OLED_WriteCommand(0xAF);  // Display on

    FL_DelayMs(100);  // Wait for the OLED to initialize
}


void OLED_Init2(void)
{
		OLED_WriteCommand(0xAE);    /* Display Off */
    OLED_WriteCommand(0x20);    /* Set Memory Addressing Mode */
    OLED_WriteCommand(0x10);    /* 00  Horizontal Addressing Mode
                               01  Vertical Addressing Mode
                               10  Page Addressing Mode (RESET)
                               11  Invalid */
    OLED_WriteCommand(0xB0);    /* Set Page Start Address for Page Addressing Mode,0-7 */
    OLED_WriteCommand(0xC8);    /* Set COM Output Scan Direction */
    OLED_WriteCommand(0x00);    /* Set Low  Column Address */
    OLED_WriteCommand(0x10);    /* Set High Column Address */
    OLED_WriteCommand(0x40);    /* Set Start Line Address */
    OLED_WriteCommand(0x81);    /* Set Contrast Control Register */
    OLED_WriteCommand(0xFF);    /* Brightness 0x00~0xff */
    OLED_WriteCommand(0xA1);    /* Set Segment Re-map 0 to 127 */
    OLED_WriteCommand(0xA6);    /* Set Normal Display */
    OLED_WriteCommand(0xA8);    /* Set Multiplex Ratio(1 to 64) */
    OLED_WriteCommand(0x3F);
    OLED_WriteCommand(0xA4);    /* 0xA4: Output Follows RAM Content
                               0xA5: Output Ignores RAM Content */
    OLED_WriteCommand(0xD3);    /* Aet Display offset */
    OLED_WriteCommand(0x00);    /* Not Offset */
    OLED_WriteCommand(0xD5);    /* Set Display Clock Divide Ratio/Oscillator Frequency */
    OLED_WriteCommand(0xF0);    /* Set Divide Ratio */
    OLED_WriteCommand(0xD9);    /* Set Pre-charge Period */
    OLED_WriteCommand(0x22);
    OLED_WriteCommand(0xDA);    /* Set Com Pins Hardware Configuration */
    OLED_WriteCommand(0x12);
    OLED_WriteCommand(0xDB);    /* Set VCOMH */
    OLED_WriteCommand(0x20);    /* 0x20=0.77*VCC */
    OLED_WriteCommand(0x8D);    /* Set DC-DC Enable */
    OLED_WriteCommand(0x14);
    OLED_WriteCommand(0xAF);    /* Turn On OLED1 Panel */
}

/*
void OLED_Init(void) //Writing is bigger with this
{
    FL_DelayMs(500);   

		OLED_WriteCommand(0xAE);  // Display off
		OLED_WriteCommand(0xD5);  // Set display clock divide ratio/oscillator frequency
		OLED_WriteCommand(0x80);  // Set divide ratio
		OLED_WriteCommand(0xA8);  // Set multiplex ratio
		OLED_WriteCommand(0x1F);  // 1/32 duty (for 128x32 display mode)
		OLED_WriteCommand(0xD3);  // Set display offset
		OLED_WriteCommand(0x00);  // No offset
		OLED_WriteCommand(0x40);  // Set display start line to 0
		OLED_WriteCommand(0x8D);  // Set charge pump
		OLED_WriteCommand(0x14);  // Enable charge pump
		OLED_WriteCommand(0x20);  // Set memory addressing mode
		OLED_WriteCommand(0x00);  // Horizontal addressing mode
		OLED_WriteCommand(0xA1);  // Set segment re-map (A0 for normal, A1 for 180 degree)
		OLED_WriteCommand(0xC0);  // Set COM output scan direction (C0 for normal, C8 for upside down)
		OLED_WriteCommand(0xDA);  // Set COM pins hardware configuration
		OLED_WriteCommand(0x02);  // Alternative COM pin configuration
		OLED_WriteCommand(0x81);  // Set contrast control
		OLED_WriteCommand(0x7F);  // Set contrast to midpoint
		OLED_WriteCommand(0xD9);  // Set pre-charge period
		OLED_WriteCommand(0xF1);  // Phase 1 = 15, Phase 2 = 1
		OLED_WriteCommand(0xDB);  // Set VCOMH deselect level
		OLED_WriteCommand(0x40);  // VCOMH deselect level ~ 0.81 x VCC
		OLED_WriteCommand(0xA4);  // Entire display ON, resume to RAM content display
		OLED_WriteCommand(0xA6);  // Set normal display
		OLED_WriteCommand(0xAF);  // Display on
		
		FL_DelayMs(100);  // Wait for the OLED to initialize
}
*/

void OLED_SetPosition(uint8_t x, uint8_t y)
{
    I2C_Start();
    I2C_WriteByte(OLED_ADDRESS << 1);
    I2C_WriteByte(0x00); // Command mode

    I2C_WriteByte(0xB0 + y); // Set page start address
    I2C_WriteByte(((x & 0xF0) >> 4) | 0x10); // Set higher column start address
    I2C_WriteByte(((x & 0x0F) >> 0) | 0x00); // Set lower column start address

    I2C_Stop();
}


void OLED_StartPosition(void)
{
    I2C_WriteByte(0x00); // Command mode
    I2C_WriteByte(0x21);   // Set Column
    I2C_WriteByte(0x19);   // Start at column 25
    I2C_WriteByte(0x7F);   // End at 128
    I2C_WriteByte(0x22);   // Set Page
    I2C_WriteByte(0x01);   // Start at page 1
    I2C_WriteByte(0x01);   // End at page 1
}

void OLED_Clear(void)
{
		// Clear display memory
		OLED_WriteCommand(0x21);  // Set column address range (0 to 127)
		OLED_WriteCommand(0x00);
		OLED_WriteCommand(0x7F);
		OLED_WriteCommand(0x22);  // Set page address range (0 to 3 for a 128x32 display)
		OLED_WriteCommand(0x00);
		OLED_WriteCommand(0x03);

		// Write zeros to clear the display memory
		for (int page = 0; page < 4; page++) {
				for (int column = 0; column < 128; column++) {
						OLED_WriteData(0x00);  // Assuming 0x00 clears the pixel (check datasheet)
				}
		}
}

/* OLED Test commands

void OLED_FillScreen(uint8_t pattern)
{
    uint8_t y, x;

    for(y = 0; y < 4; y++)  // 4 pages for 32 pixel height
    {
        OLED_WriteCommand(0xB0 + y);  // Set page address
        OLED_WriteCommand(0x00);      // Set lower column address
        OLED_WriteCommand(0x10);      // Set higher column address
        
        for(x = 0; x < 128; x++)
        {
            OLED_WriteData(pattern);
        }
    }
}

void OLED_TestPattern(void)
{
    uint8_t i, j;
    for (i = 0; i < 4; i++)  // 4 pages for 32 pixel height
    {
        OLED_WriteCommand(0xB0 + i);  // Set page address
        OLED_WriteCommand(0x00);      // Set lower column address
        OLED_WriteCommand(0x10);      // Set higher column address
        
        for (j = 0; j < 128; j++)
        {
            OLED_WriteData((i % 2) ? 0xAA : 0x55);  // Alternating pattern
        }
    }
}
*/
