#include "adc.h"
#include "batt.h"

/* VOUT = VIN * R2/(R1+R2) */
/* VIN = VOUT * (R1+R2)/R2 */
/* CH9 is the ADC in for the voltage devider */



float vbat(void)
{
    const float R1 = 138000.0f; // 138k ohms
    const float R2 = 154000.0f; // 154k ohms
    float battery_voltage;
    battery_voltage = adc_get_channel_voltage(CH9) * ((R1 + R2) / R2);
    
		return battery_voltage/1000;
}