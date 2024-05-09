/*
 * lim.c
 *
 *  Created on: May 9, 2024
 *      Author: mahir
 */

#include "lim.h"
#include "adc.h"
#include <math.h>
#include <stdio.h>

void get_lim_data(uint8_t lim_temps[NUM_LIMS]) {
	for (uint8_t i = 0; i < NUM_THERM_TOTAL; i++) {
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, i & 0x1);
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, (i >> 1) & 0x1);
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2, (i >> 2) & 0x1);

	    HAL_ADC_Start(&hadc3);
		HAL_ADC_PollForConversion(&hadc3, 100);
		uint16_t adc_data = HAL_ADC_GetValue(&hadc3);

		printf("pin: %d, adc_data: %d \n", i, adc_data);


		uint8_t avg_temp = (get_temp(adc_data) / NUM_THERM_PER_LIM);
		lim_temps[i < 3 ? 0 : 1] += avg_temp;
	}
}

uint8_t get_temp(uint16_t adc_value) {
		//Convert the ADC value being read into a resistance.
		uint32_t voltage_in = adc_value * (VOLTAGE_SUPPLY / MAX_ADC_COUNT);
		uint32_t thermistor_resistance = voltage_in * R10K / (VOLTAGE_SUPPLY - voltage_in);

		//Calculates Temperature from Resistance of thermistor using the Simplified B parameter Steinhart Equation.
		//1/Temp = 1/NominalTemp + (1/B)*1n(Thermistor Resistance/NominalResistance)
		uint8_t temp_steinhart = -ABSOLUTE_ZERO + (1.0/((1.0/ (NOMINAL_TEMPERATURE + ABSOLUTE_ZERO)) + (log(thermistor_resistance / NOMINAL_RESISTANCE) / B_COEFFICIENT)));
		return temp_steinhart;
}
