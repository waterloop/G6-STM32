#pragma once

#include <stdint.h>
#include "main.h"

#define NUM_MUX 6U //Note: the number of multiplexors must also be changed in the ADC3 configuration
#define NUM_THERM_PER_MUX 8U

#define NUM_SAMPLES 50U
#define SAMPLE_DELAY 10U

//necessary constants for Steignhart temperature calculation
#define KBiasResistance 8250U
#define KMaxAdcCount 4096U
#define KGainTranslate 1U //fill in with correct value
#define KAbsoluteZero 273.15 //fill in with correct value
#define MNominalTemperature 1U //fill in with correct value
#define MNominalThermistor 1U //fill in with correct value
#define MBCoefficient 1U //fill in with correct value

static uint8_t rear = -1;
//static uint32_t temp_data[NUM_SAMPLES][NUM_MUX];

void enqueue(uint32_t *average_mux_temp, uint32_t mux_avg[NUM_MUX], uint32_t **temp_data);
void measure_temp(uint32_t *average_mux_temp, uint32_t *adc_data, uint32_t **temp_data);
double CalculateTemperature (uint32_t adcCountUint);

