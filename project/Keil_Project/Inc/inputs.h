#ifndef __INPUTS_H__
#define __INPUTS_H__

//MENU button pin
#define MENU_GPIO   GPIOC
#define MENU_PIN    FL_GPIO_PIN_10 
#define READ_MENU_BTN()   FL_GPIO_GetInputPin(MENU_GPIO, MENU_PIN)

//POWER button pin
#define POWER_GPIO   GPIOB
#define POWER_PIN    FL_GPIO_PIN_2 
#define READ_POWER_BTN()   FL_GPIO_GetInputPin(POWER_GPIO, POWER_PIN)

//GM pulse pin
#define GM_PULSE_GPIO   GPIOA
#define GM_PULSE_PIN    FL_GPIO_PIN_8 
#define READ_GM_PULSE_PIN()   FL_GPIO_GetInputPin(GM_PULSE_GPIO, GM_PULSE_PIN)

//USB sense pin
#define USB_SENSE_GPIO   GPIOB
#define USB_SENSE_PIN    FL_GPIO_PIN_8 
#define READ_USB_SENSE_PIN()   FL_GPIO_GetInputPin(USB_SENSE_GPIO, USB_SENSE_PIN)


#endif