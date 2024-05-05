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
#define MAX_ADC_COUNT           4096U
#define ABSOLUTE_ZERO           273.15
#define NOMINAL_TEMPERATURE     25U
#define NOMINAL_RESISTANCE 	    10000U
#define B_COEFFICIENT 		    3950U

#define VOLTAGE_SUPPLY          3.3
#define R10K                    10000U


void start_dma(void);
void get_lim_data(uint16_t lim_temps[NUM_LIMS]);
uint32_t get_temp(uint16_t adc_value);

#endif /* INC_LIM_H_ */
