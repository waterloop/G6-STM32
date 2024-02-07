/*
 * DAC.c
 *
 *  Created on: Feb 6, 2024
 *      Author: Mostafa Hussein
 */

#include "DAC.h"

void DAC_init(DAC_t* dacInstance, I2C_HandleTypeDef* hi2c)
{
	dacInstance->vref = 5;
	dacInstance->dac_address = DAC_I2C_WRITE_ADDRESS;
	dacInstance->high_speed_mode = 0;
	dacInstance->hi2c = hi2c;
	reset_dac(dacInstance);
}

void DAC_write(DAC_t* dacInstance, float voltage)
{
	*(dacInstance->buffer) = calculate_code(dacInstance, voltage);
	send_command(dacInstance);
}

static uint16_t calculate_code(DAC_t* dacInstance, float voltage)
{
	voltage = fabs(voltage);
	return (uint16_t)(voltage * MAX_CODE / dacInstance->vref - DAC_OFFSET);
}

static void reset_dac(DAC_t* dacInstance)
{
	uint8_t resetTxBuffer = GENERAL_CALL_RESET;
	HAL_I2C_Master_Transmit(
				dacInstance->hi2c,
				GENERAL_CALL_ADDRESS,
				&resetTxBuffer,
				1,
				50
		);
}

static void wake_up_dac(DAC_t* dacInstance)
{
	uint8_t wakeupTxBuffer = GENERAL_CALL_WAKEUP;
	HAL_I2C_Master_Transmit(
				dacInstance->hi2c,
				GENERAL_CALL_ADDRESS,
				&wakeupTxBuffer,
				1,
				50
		);
}

static void send_command(DAC_t* dacInstance)
{
	uint16_t address = dacInstance->dac_address;
	address |= (HIGH_SPEED_MODE * dacInstance->high_speed_mode) << 8;
	HAL_I2C_Master_Transmit(
			dacInstance->hi2c,
			dacInstance->dac_address,
			dacInstance->buffer,
			2,
			50
	);
}


