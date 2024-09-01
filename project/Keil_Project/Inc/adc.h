#include "main.h"

#ifndef __ADC_H__
#define __ADC_H__


#define CH9					 FL_ADC_EXTERNAL_CH9 //batery voltage devider adc cahnnel
#define VREFINT_CAL  (*((uint16_t *)(0x1FFFFB08)))   // 30*C vref1.22 sampling value

uint32_t get_vrefint_data(void);

static uint32_t get_channel_sample_data(uint32_t channel);

uint32_t adc_get_channel_voltage(uint32_t channel);



#endif // __ADC_H__