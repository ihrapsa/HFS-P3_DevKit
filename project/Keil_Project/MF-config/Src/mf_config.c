/**
******************************************************************************
* @file           : mf_config.c
* @brief          : MCU FUNCTION CONFIG               
******************************************************************************
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
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "mf_config.h"

/* Private function prototypes -----------------------------------------------*/

 
/**
  * @brief  GPIO Initialization function
  * @param  void
  * @retval None
  */
void MF_GPIO_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    /* PA13 OUTPUT (RST_soft_I2C) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_13;
    GPIO_InitStruct.mode = FL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_ENABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    FL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* PA14 OUTPUT (HV_enable_OUT) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_14;
    GPIO_InitStruct.mode = FL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    FL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* PB3 OUTPUT (POWER_enable_OUT) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_3;
    GPIO_InitStruct.mode = FL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    FL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* PB11 OUTPUT (BUZZER) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_11;
    GPIO_InitStruct.mode = FL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    FL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* PD0 OUTPUT (SDA_soft_I2C) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_0;
    GPIO_InitStruct.mode = FL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    FL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* PD1 OUTPUT (SCL_soft_I2C) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_1;
    GPIO_InitStruct.mode = FL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    FL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* PD9 OUTPUT (LED1_red_OUT) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_9;
    GPIO_InitStruct.mode = FL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    FL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* PD10 OUTPUT (LED2_green_OUT) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_10;
    GPIO_InitStruct.mode = FL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    FL_GPIO_Init(GPIOD, &GPIO_InitStruct);    
}
 
/**
  * @brief  RCC_FOUT0 Initialization function
  * @param  void
  * @retval None
  */
void MF_RCC_FOUT0_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    /* PD11 RCC_FOUT0 */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_11;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    FL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    FL_GPIO_SetFOUT0(GPIO, FL_GPIO_FOUT0_SELECT_AHBCLK_DIV64);    
}
 
/**
  * @brief  ADC_Common Initialization function
  * @param  void
  * @retval None
  */
void MF_ADC_Common_Init(void)
{
    FL_ADC_CommonInitTypeDef    Common_InitStruct;

    Common_InitStruct.clockSource = FL_RCC_ADC_CLK_SOURCE_RCHF;
    Common_InitStruct.clockPrescaler = FL_RCC_ADC_PSC_DIV1;

    FL_ADC_CommonInit(&Common_InitStruct);    
}
 
/**
  * @brief  ADC_Sampling Initialization function
  * @param  void
  * @retval None
  */
void MF_ADC_Sampling_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_ADC_InitTypeDef    Sampling_InitStruct;

    /* PC8 ADC_IN9 (BATT_ADC_IN9) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_8;
    GPIO_InitStruct.mode = FL_GPIO_MODE_ANALOG;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    FL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    Sampling_InitStruct.conversionMode = FL_ADC_CONV_MODE_SINGLE;
    Sampling_InitStruct.autoMode = FL_ADC_SINGLE_CONV_MODE_AUTO;
    Sampling_InitStruct.waitMode = FL_ENABLE;
    Sampling_InitStruct.overrunMode = FL_ENABLE;
    Sampling_InitStruct.scanDirection = FL_ADC_SEQ_SCAN_DIR_FORWARD;
    Sampling_InitStruct.externalTrigConv = FL_ADC_TRIGGER_EDGE_NONE;
    Sampling_InitStruct.triggerSource = FL_ADC_TRGI_PA8;
    Sampling_InitStruct.fastChannelTime = FL_ADC_FAST_CH_SAMPLING_TIME_4_ADCCLK;
    Sampling_InitStruct.lowChannelTime = FL_ADC_SLOW_CH_SAMPLING_TIME_192_ADCCLK;
    Sampling_InitStruct.oversamplingMode = FL_ENABLE;
    Sampling_InitStruct.overSampingMultiplier = FL_ADC_OVERSAMPLING_MUL_16X;
    Sampling_InitStruct.oversamplingShift = FL_ADC_OVERSAMPLING_SHIFT_4B;

    FL_ADC_Init(ADC, &Sampling_InitStruct);

		FL_ADC_EnableSequencerChannel(ADC, FL_ADC_INTERNAL_TS);
		
    FL_ADC_EnableSequencerChannel(ADC, FL_ADC_INTERNAL_VREF1P2);

    FL_ADC_EnableSequencerChannel(ADC, FL_ADC_EXTERNAL_CH9);    
}
 
/**
  * @brief  EXTI Initialization function
  * @param  void
  * @retval None
  */
void MF_EXTI_Init(void)
{
    FL_EXTI_CommonInitTypeDef    EXTI_InitStruct;

    EXTI_InitStruct.clockSource = FL_RCC_EXTI_CLK_SOURCE_HCLK;

    FL_EXTI_CommonInit(&EXTI_InitStruct);    
}
 
/**
  * @brief  EXTI_Line2 Initialization function
  * @param  void
  * @retval None
  */
void MF_EXTI_Line2_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_EXTI_InitTypeDef    EXTI_InitStruct;

    /* PA8 EXTI2_Select0 (GM_pulse_IRQ) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_8;
    GPIO_InitStruct.mode = FL_GPIO_MODE_INPUT;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_ENABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    FL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    EXTI_InitStruct.input = FL_GPIO_EXTI_INPUT_GROUP0;
    EXTI_InitStruct.triggerEdge = FL_GPIO_EXTI_TRIGGER_EDGE_FALLING;
    EXTI_InitStruct.filter = FL_ENABLE;

    FL_EXTI_Init(FL_GPIO_EXTI_LINE_2, &EXTI_InitStruct);    
}
 
/**
  * @brief  EXTI_Line4 Initialization function
  * @param  void
  * @retval None
  */
void MF_EXTI_Line4_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_EXTI_InitTypeDef    EXTI_InitStruct;

    /* PB2 EXTI4_Select2 (POWER_button_IRQ) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_2;
    GPIO_InitStruct.mode = FL_GPIO_MODE_INPUT;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_ENABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    FL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    EXTI_InitStruct.input = FL_GPIO_EXTI_INPUT_GROUP2;
    EXTI_InitStruct.triggerEdge = FL_GPIO_EXTI_TRIGGER_EDGE_RISING;
    EXTI_InitStruct.filter = FL_ENABLE;

    FL_EXTI_Init(FL_GPIO_EXTI_LINE_4, &EXTI_InitStruct);    
}
 
/**
  * @brief  EXTI_Line6 Initialization function
  * @param  void
  * @retval None
  */
void MF_EXTI_Line6_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_EXTI_InitTypeDef    EXTI_InitStruct;

    /* PB8 EXTI6_Select0 (USB_sense_IRQ) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_8;
    GPIO_InitStruct.mode = FL_GPIO_MODE_INPUT;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    FL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    EXTI_InitStruct.input = FL_GPIO_EXTI_INPUT_GROUP0;
    EXTI_InitStruct.triggerEdge = FL_GPIO_EXTI_TRIGGER_EDGE_RISING;
    EXTI_InitStruct.filter = FL_ENABLE;

    FL_EXTI_Init(FL_GPIO_EXTI_LINE_6, &EXTI_InitStruct);    
}
 
/**
  * @brief  EXTI_Line10 Initialization function
  * @param  void
  * @retval None
  */
void MF_EXTI_Line10_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_EXTI_InitTypeDef    EXTI_InitStruct;

    /* PC10 EXTI10_Select2 (MENU_button_IRQ) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_10;
    GPIO_InitStruct.mode = FL_GPIO_MODE_INPUT;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_ENABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    FL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    EXTI_InitStruct.input = FL_GPIO_EXTI_INPUT_GROUP2;
    EXTI_InitStruct.triggerEdge = FL_GPIO_EXTI_TRIGGER_EDGE_FALLING;
    EXTI_InitStruct.filter = FL_ENABLE;

    FL_EXTI_Init(FL_GPIO_EXTI_LINE_10, &EXTI_InitStruct);    
}
 
/**
  * @brief  SWD_IO Initialization function
  * @param  void
  * @retval None
  */
void MF_SWD_IO_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    /* PD8 SWD_SWDIO */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_8;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    FL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* PD7 SWD_SWCLK */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_7;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    FL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    
}
 
/**
  * @brief  NVIC Initialization function
  * @param  void
  * @retval None
  */
void MF_NVIC_Init(void)
{
    FL_NVIC_ConfigTypeDef    InterruptConfigStruct;

    InterruptConfigStruct.preemptPriority = 0;
    FL_NVIC_Init(&InterruptConfigStruct, GPIO_IRQn);    
}

/**
  * @brief  HFDET_IRQHandler
  * @param  void
  * @retval None
  */
void HFDET_IRQHandler(void)
{
    //停振检测中断处理
    if((FL_FDET_IsEnabledIT_XTHFFail() == 0x01UL)
        && (FL_FDET_IsActiveFlag_XTHFFail() == 0x01UL))
    {
        FL_FDET_ClearFlag_XTHFFail();
        /*应用处理逻辑*/
    }
}


/**
  * @brief  Clock Initialization.
  * @retval None
  */
void MF_Clock_Init(void)
{
    /* Initial Low Speed Clock */
    FL_RCC_SetLSCLKClockSource(FL_RCC_LSCLK_CLK_SOURCE_LPOSC);

    /* Initial RCHF */
    FL_RCC_RCHF_SetFrequency(FL_RCC_RCHF_FREQUENCY_8MHZ);
    FL_RCC_RCHF_Enable();

    /* Initial PLL */
    FL_RCC_PLL_Disable();
    FL_RCC_PLL_SetClockSource(FL_RCC_PLL_CLK_SOURCE_RCHF);
    FL_RCC_PLL_SetPrescaler(FL_RCC_PLL_PSC_DIV8);
    FL_RCC_PLL_WriteMultiplier(47);    /* 输出48MHz */
    FL_RCC_PLL_SetOutputMultiplier(FL_RCC_PLL_OUTPUT_X1);
    FL_RCC_PLL_Enable();
    while(FL_RCC_IsActiveFlag_PLLReady() != FL_SET);

    /* Initial System Clock */
    FL_FLASH_SetReadWait(FLASH, FL_FLASH_READ_WAIT_1CYCLE);    /* 设置FLASH读等待为 1 个周期 */
    FL_RCC_SetSystemClockSource(FL_RCC_SYSTEM_CLK_SOURCE_PLL);    /* 设置系统主时钟为 PLL */
    FL_RCC_SetAHBPrescaler(FL_RCC_AHBCLK_PSC_DIV1);
    FL_RCC_SetAPB1Prescaler(FL_RCC_APB1CLK_PSC_DIV1);
    FL_RCC_SetAPB2Prescaler(FL_RCC_APB2CLK_PSC_DIV1);

    SystemCoreClockUpdate();

    /* Initial Clock Output */
    MF_RCC_FOUT0_Init();

 
}

void MF_Config_Init(void)
{
    /* Initial GPIO */
    MF_GPIO_Init();

    /* Initial ADC */
    MF_ADC_Common_Init();
    MF_ADC_Sampling_Init();

    /* Initial EXTI */
    MF_EXTI_Init();
    MF_EXTI_Line2_Init();
    MF_EXTI_Line4_Init();
    MF_EXTI_Line6_Init();
    MF_EXTI_Line10_Init();

    /* Initial SWD */
    MF_SWD_IO_Init();
		
		/* Initial NVIC */
		MF_NVIC_Init();
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{

}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 

}
#endif /* USE_FULL_ASSERT */

/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/
