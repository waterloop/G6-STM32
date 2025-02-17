/*
 * pressure.c
 *
 *  Created on: Apr 25, 2024
 *      Author: mahesh, mahir
 */

#include "pressure.h"
#include "adc.h"

uint8_t volts_to_psi (uint8_t volts){
	return (volts <= 10 ? 0.0192 : ((volts - 0.00552) / 0.00165));
}

uint8_t poll_pressure_sensor(void){
	/*
	 * I haven't used HAL_MAX_DELAY here because we will be polling
	 * two more sensors after the pressure sensor, and waiting for an
	 * ADC conversion here indefinitely will result in delays.
	*/
	HAL_ADC_PollForConversion(&hadc1, 1000);
	uint32_t raw_pressure_sensor_value = HAL_ADC_GetValue(&hadc1);

	//rawPressureSensorValue will be between 0 and 4095.
	uint8_t volts = (raw_pressure_sensor_value/MAX_ADC_VALUE) * MAX_VOLTS;

	return volts_to_psi(volts);
}
