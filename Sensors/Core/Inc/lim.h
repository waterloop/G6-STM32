/*
 * lim.h
 *
 *  Created on: Apr 20, 2024
 *      Author: mahir
 */

#ifndef INC_LIM_H_
#define INC_LIM_H_

#include <stdint.h>

#define NUM_THERM_TOTAL	 		6U
#define NUM_LIMS				2U
#define NUM_THERM_PER_LIM		NUM_THERM_TOTAL / NUM_LIMS
#define NUM_MUX 				1U

//Steinhart-Hart constants
#define BIAS_RESISTANCE 		8250U
#define MAX_ADC_COUNT 			4096U
#define GAIN_TRANSLATE 			1U 		//fill in with correct value
#define ABSOLUTE_ZERO 			273.15 	//fill in with correct value
#define NOMINAL_TEMPERATURE 	1U 		//fill in with correct value
#define NOMINAL_RESISTANCE 		1U 		//fill in with correct value
#define B_COEFFICIENT 			1U 		//fill in with correct value


void start_dma(void);
void get_lim_data(uint16_t lim_temps[NUM_LIMS]);
uint8_t get_temp(uint16_t adc_value);

#endif /* INC_LIM_H_ */
