#pragma once

#include <stdint.h>
#include "main.h"

#define NUM_MUX 6U //Note: the number of multiplexors must also be changed in the ADC3 configuration
#define NUM_THERM_PER_MUX 8U

#define NUM_SAMPLES 50U
#define SAMPLE_DELAY 10U

static uint8_t rear = -1;
//static uint32_t temp_data[NUM_SAMPLES][NUM_MUX];

void enqueue(uint32_t mux_avg[NUM_MUX], uint32_t **temp_data);
void measure_temp(uint32_t *adc_data, uint32_t **temp_data);

