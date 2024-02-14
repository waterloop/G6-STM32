/*
 * 	motor_controller.h
 *
 *  Created on: Feb 4, 2024
 *  Author: Mahir Mahota
 */

#include <string.h>
#include "motor_controller.h"

Motor_Controller_t MC_init(CAN_HandleTypeDef* handler) {
	Motor_Controller_t ret = {
		hcan = handler,
		direction = 0,
		speed = 0,
		error_code = 0,
		voltage = 0,
		current = 0,
		temp = 0
	};

	return ret;
}

void MC_stop() {
	DAC_write(throttle, 0);
	HAL_GPIO_WritePin(BRK.port, BRK.pin, GPIO_PIN_SET);
}

void MC_drive() {
	HAL_GPIO_WritePin(BRK.port, BRK.pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(REV.port, REV.pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(FW.port, FW.pin, GPIO_PIN_SET);
	DAC_write(throttle, get_voltage(DEFAULT_THROTTLE));
}

void MC_change_direction() {
	if (HAL_GPIO_ReadPin(FW.port, FW.pin)) {
		HAL_GPIO_WritePin(FW.port, FW.pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(REV.port, REV.pin, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(REV.port, REV.pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(FW.port, FW.pin, GPIO_PIN_SET);
	}
}

void MC_set_throttle(float throttle) {
	DAC_write(throttle, get_voltage(throttle));
}

uint8_t MC_get_data(Motor_Controller_Data_t* self) {
	uint8_t retval = 0;

	CAN_Frame_t frame = CAN_init(self -> hcan, MOTOR_CONTROLLER_1);


	memset(frame.data, 0, (sizeof(uint8_t) * MAX_CAN_BYTES));
}

static float get_voltage(float throttle) {

}
