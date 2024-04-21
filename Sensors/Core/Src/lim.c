/*
 * lim.c
 *
 *  Created on: Apr 20, 2024
 *      Author: mahir
 */

#include "lim.h"
#include "adc.h"
#include <math.h>

static uint32_t adc_data;

void start_dma(void) {
	HAL_ADC_Start_DMA(&hadc3, &adc_data, NUM_MUX);
}

void get_lim_data(uint16_t lim_temps[NUM_LIMS]) {
	for (uint8_t i = 0; i < NUM_THERM_TOTAL; i++) {
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, i & 0x1);
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, (i >> 1) & 0x1);
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2, (i >> 2) & 0x1);

		uint8_t avg_temp = get_temp((uint16_t) adc_data) / NUM_THERM_PER_LIM;
		lim_temps[i < 3 ? 0 : 1] += avg_temp;
	}
}

uint8_t get_temp(uint16_t adc_value) {
	// Convert the ADC value being read into a resistance.
	// R = 8250 / (4096 / (ADC * GainTranslation) - 1)
	uint32_t thermistor_resistance = BIAS_RESISTANCE / ((MAX_ADC_COUNT / (adc_value * GAIN_TRANSLATE)) - 1.0);

	// Calculates Temperature from Resistance of thermistor using the Simplified B parameter Steinhart Equation.
	// 1/Temp = 1/NominalTemp + (1/B)*1n(Thermistor Resistance/NominalResistance)
	return (-ABSOLUTE_ZERO + (1.0 / ((1.0 / (NOMINAL_TEMPERATURE + ABSOLUTE_ZERO)) + (log(thermistor_resistance / NOMINAL_RESISTANCE) / B_COEFFICIENT))));
}
