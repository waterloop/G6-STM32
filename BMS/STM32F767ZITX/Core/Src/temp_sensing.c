#include "temp_sensing.h"


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
