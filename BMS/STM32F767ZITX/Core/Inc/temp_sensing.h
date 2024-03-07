#pragma once

#include <stdint.h>
#include "main.h"

#define NUM_MUX 6U //Note: the number of multiplexors must also be changed in the ADC3 configuration
#define NUM_THERM_PER_MUX 8U

#define NUM_SAMPLES 50U

int system_init(void);
int measure_temp(uint32_t adc_data[NUM_MUX]);

