/**
  ****************************************************************************************************
  * @file    main.c
  * @author  FMSH Application Team
  * @brief   Header file of FL Module
  ****************************************************************************************************
  * @attention
  *
  * Copyright (c) [2021] [Fudan Microelectronics]
  * THIS SOFTWARE is licensed under Mulan PSL v2.
  * can use this software according to the terms and conditions of the Mulan PSL v2.
  * You may obtain a copy of Mulan PSL v2 at:
  *          http://license.coscl.org.cn/MulanPSL2
  * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, 
  * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, 
  * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
  * See the Mulan PSL v2 for more details.
  *
  ****************************************************************************************************
  */

#include "main.h"
#include "fm33_assert.h"
#include "I2C_bitbang.h"
#include "oled.h"
#include "oled_draw.h"
#include "LEDs.h"


/**    
* Chip Series: FM33LC0xx;
* FL Version: v2.3;
* Project Name: HFS-P3_reveng_I2C_LEDs;
* Project Version: v2.3.0.0;
* Project ID: 1804577435702308865;
* Create Date: 2024-06-23;
*/

  
int main(void)
{
    /* Initialize FL Driver Library */
    FL_Init();

    /* Configure the system clock */
    MF_Clock_Init();
    
   
    /* Initialize all configured peripherals */
    MF_Config_Init();
	
	  /* Initialize I2C */
    I2C_Init();
    
    /* Initialize OLED */
		OLED_HardwareReset();  // Perform hardware reset first
		OLED_Init();
		//OLED_Init2();
		//OLED_SetPosition(0, 0);
		OLED_Clear();
		//OLED_WriteDataList(ALPHABET, sizeof(ALPHABET));
		//OLED_ShowChar(10,10,'Q',12);
		//OLED_StartPosition();
		OLED_ShowText(10,10,"Hecked ",7);
		OLED_WriteDataList(skull, sizeof(skull));

    
		while(1)
    {     
			/*
				OLED_FillScreen(0xAA);  // 10101010 pattern
        FL_DelayMs(1000);
        OLED_FillScreen(0x55);  // 01010101 pattern
        FL_DelayMs(1000);
			*/
			LED1_ON();
			FL_DelayMs(1000);
			LED1_OFF();
			
			LED2_ON();
			FL_DelayMs(1000);
			LED2_OFF();

    }

}


