/*
 * armi_adc.c
 *
 *  Created on: Nov 15, 2024
 *      Author: KimTeddy
 */

#include "armi_adc.h"

uint8_t batt_level = 0;

uint8_t armi_batt_lower_than_mv(int batt_limit) {
	uint16_t adc_value = 0;
	uint16_t batt_mv = 0;

	HAL_ADC_Start(&hadc1);
	if (HAL_ADC_PollForConversion(&hadc1, 240) == HAL_OK) {
		adc_value = HAL_ADC_GetValue(&hadc1);
	}
	HAL_ADC_Stop(&hadc1);

	// Calculate battery voltage in mV
	batt_mv = (uint16_t) ((adc_value / 16383.0) * 3300 * 2);
	// Calculate battery percentage based on voltage
	if (batt_mv >= 4200) {
		batt_level = 100; // Maximum: 100%
	} else if (batt_mv <= 3000) {
		batt_level = 0; // Minimum: 0%
	} else {
		// Percentage calculation: (current voltage - min voltage) / (max voltage - min voltage) * 100
		batt_level = (uint8_t) (((batt_mv - 3000) * 100) / (4200 - 3000));
	}
#ifdef DEBUG
	my_printf("Battery: %d mV\n\r", batt_mv);
#endif
	if (batt_mv < batt_limit) //low battery 3000
			{
		return 1;
	} else {
		return 0;
	}
}
