#include "temp.h"
#include "adc.h"


static uint32_t GetTSSample_IRQ(void)
{
    uint16_t ADCRdresult;
    uint32_t i = 0;
    uint32_t time = 0;

    if (FL_ADC_IsEnabledOverSampling(ADC))
    {
        time = (1600 * 2) << (FL_ADC_GetOverSamplingMultiplier(ADC) >> 17);   
    }
    else
    {
        time = 1600;
    }

    FL_RCC_SetADCPrescaler(FL_RCC_ADC_PSC_DIV8);
    FL_VREF_EnableVPTATBuffer(VREF);
    FL_ADC_DisableSequencerChannel(ADC, FL_ADC_ALL_CHANNEL); // Clear all channels
    FL_ADC_EnableSequencerChannel(ADC, FL_ADC_INTERNAL_TS); // Select the temperature sensor channel

    FL_ADC_ClearFlag_EndOfConversion(ADC); // Clear EOC flag
    FL_ADC_Enable(ADC); // Start ADC
    FL_ADC_EnableSWConversion(ADC); // Start Conversion

    // Wait until the conversion is complete or timeout occurs
    while (ADCComplete == 0)
    {
        if (i >= time)
        {
            break;
        }
        i++;
        FL_DelayUs(1);
    }

    ADCComplete = 0; // Reset the ADC complete flag
    FL_ADC_ClearFlag_EndOfConversion(ADC); // Clear EOC flag
    ADCRdresult = FL_ADC_ReadConversionData(ADC); // Get the ADC result

    FL_ADC_Disable(ADC); // Disable ADC
    FL_ADC_DisableSequencerChannel(ADC, FL_ADC_INTERNAL_TS); // Disable the TS channel
    FL_VREF_DisableVPTATBuffer(VREF); // Disable VPTAT buffer
    
    return ADCRdresult;
}


float GetTS_IRQ(void)
{
    uint32_t Get122VSample, VPTAT, VPTAT_30;
    uint64_t GetTSSample;
    float GetTS;

    // Step 1: Get the reference voltage sample using interrupt
    Get122VSample = get_vrefint_data_IRQ();
    
    // Step 2: Get the temperature sensor sample using interrupt
    GetTSSample = GetTSSample_IRQ();
    
    // Step 3: Calculate the voltage corresponding to the temperature
    VPTAT = (GetTSSample * 3000 * (VREFINT_CAL)) / (Get122VSample * 4095);
    VPTAT_30 = (TS_CAL1 * 3000) / (4095);

    // Step 4: Calculate the temperature using the factory calibration
    GetTS = (float)(VPTAT * 1.0 - VPTAT_30 * 1.0) / (2.97) + 30 - 2;
    
    return GetTS;
}