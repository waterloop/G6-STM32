/*
 * dac.c
 *
 *  Created on: Feb 6, 2024
 *      Author: Mostafa Hussein, Mahir Mahota
 */

#include "dac.h"

DAC_t DAC_init(I2C_HandleTypeDef* hi2c)
{
	DAC_t dacInstance;
	dacInstance.vref = 5;
	dacInstance.dac_address = DAC_I2C_WRITE_ADDRESS;
	dacInstance.high_speed_mode = 0;
	dacInstance.hi2c = hi2c;
	dacInstance.current_val = 2.5;
	reset_dac(dacInstance);
	DAC_write(dacInstance, 0);

	return dacInstance;
}

void DAC_write(DAC_t dacInstance, float voltage)
{
	if (dacInstance.current_val < voltage)
	{
		for(float temp_voltage = dacInstance.current_val; temp_voltage < voltage; temp_voltage += 0.005)
		{
			uint16_t tempVal = calculate_code(dacInstance, temp_voltage);
			dacInstance.buffer[0] = tempVal >> 8 & 0xFF;
			dacInstance.buffer[1] = tempVal & 0xFF;
			send_command(dacInstance);
			dacInstance.current_val = temp_voltage;
			HAL_Delay(200);
		}
	}
	else
	{
		for(float temp_voltage = dacInstance.current_val; temp_voltage > voltage; temp_voltage -= 0.005)
		{
			uint16_t tempVal = calculate_code(dacInstance, temp_voltage);
			dacInstance.buffer[0] = tempVal >> 8 & 0xFF;
			dacInstance.buffer[1] = tempVal & 0xFF;
			send_command(dacInstance);
			dacInstance.current_val = temp_voltage;
			HAL_Delay(200);
		}
	}
}

uint16_t calculate_code(DAC_t dacInstance, float voltage)
{
	voltage = fabs(voltage);
	return (uint16_t)(voltage * MAX_CODE / dacInstance.vref * DAC_GAIN - DAC_OFFSET);
}

void reset_dac(DAC_t dacInstance)
{
	uint8_t resetTxBuffer = GENERAL_CALL_RESET;
	HAL_I2C_Master_Transmit(
				dacInstance.hi2c,
				GENERAL_CALL_ADDRESS,
				&resetTxBuffer,
				1,
				50
		);
}

void wake_up_dac(DAC_t dacInstance)
{
	uint8_t wakeupTxBuffer = GENERAL_CALL_WAKEUP;
	HAL_I2C_Master_Transmit(
				dacInstance.hi2c,
				GENERAL_CALL_ADDRESS,
				&wakeupTxBuffer,
				1,
				50
		);
}

void send_command(DAC_t dacInstance)
{
	uint16_t address = dacInstance.dac_address;
	address |= (HIGH_SPEED_MODE * dacInstance.high_speed_mode) << 8;
	HAL_I2C_Master_Transmit(
			dacInstance.hi2c,
			address<<1,
			dacInstance.buffer,
			2,
			50
	);
}


