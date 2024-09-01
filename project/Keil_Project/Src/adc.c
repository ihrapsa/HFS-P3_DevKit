#include "adc.h"

uint32_t get_vrefint_data(void)
{
    uint16_t adc_result;
    uint8_t i = 0;
    FL_RCC_SetADCPrescaler(FL_RCC_ADC_PSC_DIV8);
    FL_VREF_EnableVREFBuffer(VREF); // Enable VREF BUFFER
    FL_ADC_EnableSequencerChannel(ADC, FL_ADC_INTERNAL_VREF1P2); // Select VREF channel
    
    FL_ADC_ClearFlag_EndOfConversion(ADC); // Clear the conversion complete flag
    FL_ADC_Enable(ADC); // Start the ADC
    FL_ADC_EnableSWConversion(ADC); // Start the conversion
    
    // Wait for the conversion to complete
    while(FL_ADC_IsActiveFlag_EndOfConversion(ADC) == FL_RESET)
    {
        if(i >= 5)
        {
            break;
        }

        i++;
        FL_DelayMs(1);
    }
    
    FL_ADC_ClearFlag_EndOfConversion(ADC); // Clear the conversion complete flag
    adc_result = FL_ADC_ReadConversionData(ADC); // Get the sampled value

    FL_ADC_Disable(ADC); // Disable the ADC
    FL_ADC_DisableSequencerChannel(ADC, FL_ADC_INTERNAL_VREF1P2); // Close the VREF channel
    FL_VREF_DisableVREFBuffer(VREF); // Disable VREF BUFFER
    // Return the conversion result
    return adc_result;
}

static uint32_t get_channel_sample_data(uint32_t channel)
{
    uint16_t adc_result;
    uint8_t i = 0;
    FL_RCC_SetADCPrescaler(FL_RCC_ADC_PSC_DIV1);
    FL_ADC_EnableSequencerChannel(ADC, channel); // Select the channel

    FL_ADC_ClearFlag_EndOfConversion(ADC); // Clear the conversion complete flag
    FL_ADC_Enable(ADC); // Start the ADC
    FL_ADC_EnableSWConversion(ADC); // Start the conversion

    // Wait for the conversion to complete
    while(FL_ADC_IsActiveFlag_EndOfConversion(ADC) == FL_RESET)
    {
        if(i >= 5)
        {
            break;
        }

        i++;
        FL_DelayMs(1);
    }

    FL_ADC_ClearFlag_EndOfConversion(ADC); // Clear the conversion complete flag
    adc_result = FL_ADC_ReadConversionData(ADC); // Get the sampled value

    FL_ADC_Disable(ADC); // Disable the ADC
    FL_ADC_DisableSequencerChannel(ADC, channel); // Close the channel
    // Return the conversion result
    return adc_result;
}

uint32_t adc_get_channel_voltage(uint32_t channel)
{
    uint32_t vrefint_data, adc_voltage;
    uint64_t adc_data;

    vrefint_data = get_vrefint_data();
    adc_data = get_channel_sample_data(channel);
    adc_voltage = (adc_data * 3000 * (VREFINT_CAL)) / (vrefint_data * 4095);
    // Return the conversion result
    return adc_voltage;
}
