#include "i2c_bitbang.h"


#define OLED_ADDRESS 0x3C // SSD1316 OLED display I2C address
#define OLED_WIDTH 128 // OLED display width
#define OLED_HEIGHT 32 // OLED display height
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
	


//void OLED_SetCursor_page_mode(uint8_t x, uint8_t y) {

//    I2C_Start();
//    I2C_WriteByte(OLED_ADDRESS << 1);
//    I2C_WriteByte(0x00);  // Command mode
//	
//    I2C_WriteByte(0x21);  //Set column adress
//    I2C_WriteByte(x); //Start
//    I2C_WriteByte(OLED_WIDTH - 1); //End
//		I2C_WriteByte(0x22); // Set page address (line)
//    I2C_WriteByte(y); //Start
//    I2C_WriteByte(OLED_HEIGHT / 8 - 1); //End
//		I2C_Stop();
//}
//
//void OLED_Clear(void) //Page addressing mode
//{
//    for (int page = 0; page < (OLED_HEIGHT / 8); page++) {
//        OLED_SetCursor_page_mode(0, page); // Set the cursor to the start of each page
//        for (int column = 0; column < OLED_WIDTH; column++) {
//            OLED_WriteData(0x00); // Write zero to clear the display
//        }
//    }
//}


void OLED_SetCursor(uint8_t x, uint8_t y)
{
    if (x >= 128) x = 127; // Limit x (column) to 127
    if (y >= 32) y = 31;   // Limit y (row) to 31

    // Calculate page based on y
    uint8_t page = y / 8;

	  // Calculate row offset within the page
    uint8_t rowOffset = y % 8;
	
    // Set Column Address
    OLED_WriteCommand(0x21);          // Set Column Address command
    OLED_WriteCommand(x);             // Start Column Address (0-127)
    OLED_WriteCommand(OLED_WIDTH - 1);           // End Column Address (0-127)

    // Set Page Address
    OLED_WriteCommand(0x22);          // Set Page Address command
    OLED_WriteCommand(page);          // Start Page Address (0-3)
    OLED_WriteCommand(OLED_HEIGHT / 8 - 1);          // End Page Address (0-3)

    // Adjust for vertical offset if needed
    // This might involve setting a display offset if supported by your display configuration
}



void OLED_Clear(void) //Horizontal addressing mode
{
		I2C_Start();
    I2C_WriteByte(OLED_ADDRESS << 1);
    I2C_WriteByte(0x40);  // Data mode
        
		for (int column = 0; column < OLED_WIDTH*(OLED_HEIGHT/8); column++) {
			I2C_WriteByte(0x00); // Write zero to clear the display
    }
		   
    I2C_Stop();
}


void OLED_Init(void)
{
 OLED_WriteCommand(0xAE); // Set Display Off 
 OLED_WriteCommand(0xD5); // Display divide ratio/osc. freq. mode 
 OLED_WriteCommand(0xC1); // 115HZ 
 OLED_WriteCommand(0xA8); // Multiplex ration mode: 
 OLED_WriteCommand(0x1F); 
 OLED_WriteCommand(0xAD); // External or Internal VCOMH/ IREF Selection 
 OLED_WriteCommand(0x00); // Internal VCOMH/ External IREF 
 OLED_WriteCommand(0x20); // Set Memory Addressing Mode 
 OLED_WriteCommand(0x00); // Horizontal Addressing Mode (0x0,0x1, 0x2 for horizontal,vertical, page) 
 OLED_WriteCommand(0xD3); // Set Display Offset 
 OLED_WriteCommand(0x00); 
 OLED_WriteCommand(0x40); // Set Display Start Line 
 OLED_WriteCommand(0x8D); // DC-DC Control Mode Set 
 OLED_WriteCommand(0x14); // DC-DC ON/OFF Mode Set 
 OLED_WriteCommand(0xA1); // Segment remap (0xA0 normal, 0xA1 mirrored)
 OLED_WriteCommand(0xC0); // Set COM Output Scan Direction (0xC8 normal, 0xC0 flipped)
 OLED_WriteCommand(0xDA); // Seg pads hardware: alternative 
 OLED_WriteCommand(0x12); 
 OLED_WriteCommand(0x81); // Contrast control 
 OLED_WriteCommand(0x53); 
 OLED_WriteCommand(0xD9); // Set pre-charge period 
 OLED_WriteCommand(0x22); 
 OLED_WriteCommand(0xDB); // VCOMH deselect level mode 
 OLED_WriteCommand(0x00); 
 OLED_WriteCommand(0xA4); // Set Entire Display On/Off 
 OLED_WriteCommand(0xA6); // Set Normal Display 
 OLED_Clear(); 
 OLED_WriteCommand(0xAF); // Set Display On
}
