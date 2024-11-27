/*
 * armi_adc.h
 *
 *  Created on: Nov 15, 2024
 *      Author: KimTeddy
 */

#ifndef INC_ARMI_ADC_H_
#define INC_ARMI_ADC_H_

#include "main.h"
#include "adc.h"

extern uint8_t batt_level;

uint8_t armi_batt_lower_than_mv(int batt_limit);

#endif /* INC_ARMI_ADC_H_ */
