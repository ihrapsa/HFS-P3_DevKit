#include "gpio_interrupt.h"
#include "main.h"
#include "leds.h"
#include "buzzer.h"
#include "outputs.h"
#include "inputs.h"


void GPIO_IRQHandler(void)
{
		// Enable GM tube on button press
    if(FL_GPIO_IsActiveFlag_EXTI(GPIO, MENU_BTN))
    {
        FL_GPIO_ClearFlag_EXTI(GPIO, MENU_BTN);
        LED1_ON();
				FL_DelayMs(500);
				play_click();
				LED1_OFF();
				HV_EN_ON();
				
    }
		
		// Click buzzer on radioactive decay
		if(FL_GPIO_IsActiveFlag_EXTI(GPIO, GM_PULSE))
    {
        FL_GPIO_ClearFlag_EXTI(GPIO, GM_PULSE);
			
				LED2_ON();
				play_click_500us();
				FL_DelayMs(100);
				LED2_OFF();

				
    }
		
		// Power on/off sequence
		if(FL_GPIO_IsActiveFlag_EXTI(GPIO, POWER_BTN))
    {
        FL_GPIO_ClearFlag_EXTI(GPIO, POWER_BTN);
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
		
}