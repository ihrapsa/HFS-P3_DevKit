#include "temp.h"
#include "adc.h"

static uint32_t GetTSSample_POLL(void)
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
    FL_VREF_EnableVPTATBuffer(VREF);
    FL_ADC_DisableSequencerChannel(ADC, FL_ADC_ALL_CHANNEL); // Clear the opened channels
    FL_ADC_EnableSequencerChannel(ADC, FL_ADC_INTERNAL_TS);  // Select the channel

    FL_ADC_ClearFlag_EndOfConversion(ADC); // Clear the conversion end flag
    FL_ADC_Enable(ADC);      // Start ADC
    FL_ADC_EnableSWConversion(ADC);  // Start conversion

    // Wait for the conversion to complete
    while(FL_ADC_IsActiveFlag_EndOfConversion(ADC) == FL_RESET)
    {
        if(i >= time)
        {
            break;
        }

        i++;
        FL_DelayUs(1);
    }

    FL_ADC_ClearFlag_EndOfConversion(ADC); // Clear the conversion end flag
    ADCRdresult = FL_ADC_ReadConversionData(ADC); // Get the sample value

    FL_ADC_Disable(ADC);    // Disable ADC
    FL_ADC_DisableSequencerChannel(ADC, FL_ADC_INTERNAL_TS); // Disable the channel
    FL_VREF_DisableVPTATBuffer(VREF);
    // Return the conversion result
    return ADCRdresult;
}


float GetTS_POLL(void)
{
    uint32_t Get122VSample, VPTAT, VPTAT_30;
    uint64_t GetTSSample;
    float GetTS;

    Get122VSample = get_vrefint_data();
    GetTSSample = GetTSSample_POLL();
    VPTAT = (GetTSSample * 3000 * (VREFINT_CAL)) / (Get122VSample * 4095);
    VPTAT_30 = (TS_CAL1 * 3000) / (4095);

    GetTS = (float)(VPTAT * 1.0 - VPTAT_30 * 1.0) / (2.97) + 30 - 2;
    // return conversion
    return GetTS;
}
