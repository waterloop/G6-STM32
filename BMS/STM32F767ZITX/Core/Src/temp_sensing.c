#include "temp_sensing.h"
#include <stdio.h>

#define AVERAGE_SET_NUM 5
#define MUX_NUM 4
#define NUM_THERMISTORS 12

struct Temperature_Table {
  double temp_table[MUX_NUM][NUM_THERMISTORS]; //2D array containing a row for each MUX with 13 entries, 12 temperatures from each associated thermistor and one average
};

//circular queue implementation for containing average temperature
int ave_temperature_data[AVERAGE_SET_NUM][MUX_NUM];
int rear = -1;

// Adding an average_temperature_row (if full, will overwrite rear
//average_temperature_row is an array of the average temperatures for each MUX
void enQueue(int average_temperature_row[]) {
	rear = (rear + 1) % AVERAGE_SET_NUM;
	for (int i = 0; i < MUX_NUM; i++){
		ave_temperature_data[rear][i] = average_temperature_row[i];
	}
}

//Not sure how much initialize the HAL will handle.
//We might need this, might not.
int system_init(void)
{

	return 0;
}

//function input is the thermistor data for each MUX
int measure_temp(uint32_t adc_data[NUM_MUX])
{
	uint32_t mux_avg[NUM_MUX] = {0};

	for(uint8_t i=0U; i<NUM_THERM_PER_MUX; ++i)
	{
		//Code for setting control lines.
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, i & 0x1);
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2, i>>1 & 0x1);
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, i>>2 & 0x1);

		//Code for reading thermistor value.
		for(uint8_t i=0U; i<NUM_MUX; ++i)
		{
			mux_avg[i] += adc_data[i] / NUM_THERM_PER_MUX;
		}
	}

	return 0;
}
