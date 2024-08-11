		#define LED1_GPIO   GPIOD
		#define LED1_PIN    FL_GPIO_PIN_9 //RED LED

		#define LED1_OFF()   FL_GPIO_ResetOutputPin(LED1_GPIO, LED1_PIN)
		#define LED1_ON()  FL_GPIO_SetOutputPin(LED1_GPIO, LED1_PIN)
		#define LED1_TOG()  FL_GPIO_ToggleOutputPin(LED1_GPIO, LED1_PIN)

		#define LED2_GPIO   GPIOD
		#define LED2_PIN    FL_GPIO_PIN_10 //GREEN LED

		#define LED2_OFF()   FL_GPIO_ResetOutputPin(LED2_GPIO, LED2_PIN)
		#define LED2_ON()  FL_GPIO_SetOutputPin(LED2_GPIO, LED2_PIN)	
		#define LED2_TOG()  FL_GPIO_ToggleOutputPin(LED2_GPIO, LED2_PIN)