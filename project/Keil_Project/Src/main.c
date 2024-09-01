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
#include "oled_draw.h"
#include "gpio_interrupt.h"

#include "adc.h"
#include "batt.h"
#include "temp.h"

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
		//OLED_Clear(); //Already in OLED_Init()
		
		/*Show something on oled */
//		OLED_SetCursor(15, 15);
//		OLED_ShowText("Hecked ",7);
//		OLED_ShowText("Hecked ",7);
//		OLED_ShowText("Hecked ",7);
//		OLED_ShowText("150mSv/h ",7);
//		OLED_WriteDataList(skull, sizeof(skull));
//		
    while(1)
    {
			// Get Battery Voltage
			float BattVoltage = vbat();
			char VoltageStr[10];
			snprintf(VoltageStr, sizeof(VoltageStr), "%.3f V", BattVoltage);
			
			//OLED_Clear();
			OLED_SetCursor(15, 15);
			OLED_ShowText(VoltageStr ,7);
			
			// Get Internal Temperature
			
			float GetT = GetTS_IRQ();
			char TempStr[10];
			snprintf(TempStr, sizeof(TempStr), "%.2f *C", GetT);
			
			OLED_SetCursor(15, 25);
			OLED_ShowText(TempStr ,7);
			FL_DelayMs(3000);
			
    }

}

