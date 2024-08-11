#ifndef __OUTPUTS_H__
#define __OUTPUTS_H__


//Power Enable Output Pin
#define POWER_EN_GPIO   GPIOB
#define POWER_EN_PIN    FL_GPIO_PIN_3 

#define POWER_EN_OFF()  FL_GPIO_ResetOutputPin(POWER_EN_GPIO, POWER_EN_PIN) // Will switch battery source Off
#define POWER_EN_ON()  	FL_GPIO_SetOutputPin(POWER_EN_GPIO, POWER_EN_PIN) // Will switch battery source On
#define READ_POWER_EN()	FL_GPIO_GetOutputPin(POWER_EN_GPIO, POWER_EN_PIN) // Reads the status of the GPIO


//Buzzer Pin
#define BUZZER_GPIO   GPIOB
#define BUZZER_PIN    FL_GPIO_PIN_11

#define BUZZER_OFF()  FL_GPIO_ResetOutputPin(BUZZER_GPIO, BUZZER_PIN) // Will turn buzzer Off
#define BUZZER_ON()  	FL_GPIO_SetOutputPin(BUZZER_GPIO, BUZZER_PIN) // Will turn buzzer On
#define READ_BUZZER()	FL_GPIO_GetOutputPin(BUZZER_GPIO, BUZZER_PIN)


//High Voltage PSU Pin
#define HV_PSU_GPIO   GPIOA
#define HV_PSU_PIN    FL_GPIO_PIN_14

#define HV_PSU_OFF() 	FL_GPIO_ResetOutputPin(HV_PSU_GPIO, HV_PSU_PIN) // ?
#define HV_PSU_ON()  	FL_GPIO_SetOutputPin(HV_PSU_GPIO, HV_PSU_PIN) // ?
#define READ_HV_PSU()	FL_GPIO_GetOutputPin(HV_PSU_GPIO, HV_PSU_PIN)


#endif