#include "adc.h"

uint8_t ADCComplete = 0;
void ADC_IRQHandler(void)
{

    if((FL_ENABLE == FL_ADC_IsEnabledIT_EndOfConversion(ADC))
            && (FL_SET == FL_ADC_IsActiveFlag_EndOfConversion(ADC)))
    {
        FL_ADC_ClearFlag_EndOfConversion(ADC);//Clear Flag
        ADCComplete = 1;

    }

}


uint32_t get_vrefint_data_IRQ(void)
{
    uint16_t ADCRdresult;
    uint32_t i = 0;
    uint32_t time = 0;
    if(FL_ADC_IsEnabledOverSampling(ADC))
    {
        time = (1600*2) << (FL_ADC_GetOverSamplingMultiplier(ADC)>>17);   
    }
    else
        time = 1600;
    FL_RCC_SetADCPrescaler(FL_RCC_ADC_PSC_DIV8);
    FL_VREF_EnableVREFBuffer(VREF); // Enable the VREF buffer
    FL_ADC_DisableSequencerChannel(ADC, FL_ADC_ALL_CHANNEL); // Clear all open channels
    FL_ADC_EnableSequencerChannel(ADC, FL_ADC_INTERNAL_VREF1P2); // Select VREF as the channel

    FL_ADC_ClearFlag_EndOfConversion(ADC); // Clear the end of conversion flag
    FL_ADC_Enable(ADC); // Start the ADC
    FL_ADC_EnableSWConversion(ADC); // Start the conversion

    // Wait for the conversion to complete
    while(ADCComplete == 0)
    {
        if(i >= time)
        {
            break;
        }

        i++;
        FL_DelayUs(1);
    }

    ADCComplete = 0;
    FL_ADC_ClearFlag_EndOfConversion(ADC); // Clear the end of conversion flag
    ADCRdresult = FL_ADC_ReadConversionData(ADC); // Get the sampled value

    FL_ADC_Disable(ADC); // Disable the ADC
    FL_ADC_DisableSequencerChannel(ADC, FL_ADC_INTERNAL_VREF1P2); // Close the VREF channel
    FL_VREF_DisableVREFBuffer(VREF); // Disable the VREF buffer
    // Return the conversion result
    return ADCRdresult;
}


static uint32_t get_channel_sample_data_IRQ(uint32_t channel)
{
    uint16_t ADCRdresult;
    uint32_t i = 0;
    uint32_t time = 0;
    if(FL_ADC_IsEnabledOverSampling(ADC))
    {
        time = (1600*2) << (FL_ADC_GetOverSamplingMultiplier(ADC)>>17);   
    }
    else
        time = 1600;
    FL_RCC_SetADCPrescaler(FL_RCC_ADC_PSC_DIV1);
    FL_ADC_DisableSequencerChannel(ADC, FL_ADC_ALL_CHANNEL); // Clear all open channels
    FL_ADC_EnableSequencerChannel(ADC, channel); // Select the specified channel

    FL_ADC_ClearFlag_EndOfConversion(ADC); // Clear the end of conversion flag
    FL_ADC_Enable(ADC); // Start the ADC
    FL_ADC_EnableSWConversion(ADC); // Start the conversion

    // Wait for the conversion to complete
    while(ADCComplete == 0)
    {
        if(i >= time)
        {
            break;
        }

        i++;
        FL_DelayUs(1);
    }

    ADCComplete = 0;
    FL_ADC_ClearFlag_EndOfConversion(ADC); // Clear the end of conversion flag
    ADCRdresult = FL_ADC_ReadConversionData(ADC); // Get the sampled value

    FL_ADC_Disable(ADC); // Disable the ADC
    FL_ADC_DisableSequencerChannel(ADC, channel); // Close the specified channel
    // Return the conversion result
    return ADCRdresult;
}


uint32_t adc_get_channel_voltage(uint32_t channel)
{
    uint32_t vrefint_data, adc_voltage;
    uint64_t adc_data;

    vrefint_data = get_vrefint_data_IRQ();
    adc_data = get_channel_sample_data_IRQ(channel);
    adc_voltage = (adc_data * 3000 * (VREFINT_CAL)) / (vrefint_data * 4095);
    // Return the conversion result
    return adc_voltage;
}
