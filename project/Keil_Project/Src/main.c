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
#include "leds.h"
#include "inputs.h"
#include "outputs.h"
#include "buzzer.h"
#include "oled_i2c.h"
#include "oled_Draw.h"

/**    
* Chip Series: FM33LC0xx;
* FL Version: v2.3;
* Project Name: HFS-P3_base_configured;
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
    
    /* Initialize all configured peripherals including SWD, all GPIOs, I2C soft pins, WKUP2  */
    MF_Config_Init();
	
	
		/* Initialize OLED */
		OLED_HardwareReset();  // Perform hardware reset first
		OLED_Init();
		OLED_Clear();


    while(1)
    {
			if(READ_POWER_BTN() == 0)
				{
					if(READ_POWER_EN() == 0)
					{
						POWER_EN_ON(); //Enable battery source
						play_beep(); //Play a beep
						LED2_ON(); //Turn on Green LED
						FL_DelayMs(1000);
						LED2_OFF();
					}
					else if(READ_POWER_EN() == 1)
					{
						play_beep(); //play a goodbye beep
						FL_DelayMs(500);
						play_beep();
						POWER_EN_OFF(); //Disable battery source
					}
				}
			
			// Check if button is pressed (active low because of pull-up)
			if(READ_MENU_PIN() == 0)
			{	
				
				// Infinite beep loop
				int t = 1;
				while(t == 1)
				{
					if(READ_MENU_PIN() == 0) //Exit loop if button pressed again - WIP not working
					{
						t = 0;
					}
					play_beep();
					LED1_ON(); //LED1 red in sync with beep
					FL_DelayMs(500);
					
					play_beep();
					LED1_OFF();
					FL_DelayMs(1000);
							
					OLED_ShowText(10,10,"Hecked ",7);
					OLED_WriteDataList(skull, sizeof(skull));
				}
			}
    }

}


