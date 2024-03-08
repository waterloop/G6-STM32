#include "temp_sensing.h"
#include <stdio.h>


//Function Description: Adds temperature sample to array stored in memory and updates final average temperature table
//Inputs: average_mux_temp(old array of average temperatures for each MUX over n samples), mux_temp(array containing 1 sample of MUX temperature data), temp_data(array stored in memory containing past n temperature samples)
//Outputs: average_mux_temp(updated array of average temperatures for each MUX over n samples), temp_data(modified temperature array)
void enqueue(uint32_t *average_mux_temp, uint32_t mux_temp[NUM_MUX], uint32_t **temp_data) {
	rear = (rear + 1) % NUM_SAMPLES;
	for (uint8_t i = 0U; i < NUM_MUX; ++i){
		average_mux_temp[i] -= temp_data[rear][i] / NUM_SAMPLES;
		temp_data[rear][i] = mux_temp[i];
		average_mux_temp[i] += temp_data[rear][i] / NUM_SAMPLES;
	}
	return;
}


//Function Description: Measures average thermistor temperature of each MUX
//Inputs: adc_data(array containing measured values from ADCs), temp_data(array stored in memory containing past n temperature samples)
//Outputs: temp_data(modified temperature array)
void measure_temp(uint32_t *average_mux_temp, uint32_t *adc_data, uint32_t **temp_data)
{
	uint32_t mux_temp[NUM_MUX] = {0};
	for(uint8_t i = 0U; i < NUM_THERM_PER_MUX; ++i){
		//Increment orientation of MUX control lines.
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, i & 0x1);
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2, i>>1 & 0x1);
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, i>>2 & 0x1);

		//Record average temperature of each MUX.
		for(uint8_t i = 0U; i < NUM_MUX; ++i){
			mux_temp[i] += adc_data[i] / NUM_THERM_PER_MUX;
		}
	}
	enqueue(average_mux_temp, mux_temp, temp_data);

	return;
}
