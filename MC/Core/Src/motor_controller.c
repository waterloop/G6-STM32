/*
 * 	motor_controller.h
 *
 *  Created on: Feb 4, 2024
 *  Author: Mahir Mahota
 */

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

void MC_get_data(Motor_Controller_Data_t* self) {

	CAN_Frame_t frame_1 = CAN_init(self->hcan, MOTOR_CONTROLLER_1);
	CAN_Frame_t frame_2 = CAN_init(self->hcan, MOTOR_CONTROLLER_2);
	frame_1.id_type = CAN_ID_EXT;
	frame_1.data_length = 0;
	frame_2.id_type = CAN_ID_EXT;
	frame_2.data_length = 0;

	CAN_send_frame(frame_1);
	uint8_t recieved = 0;
	while (!recieved) {
		if (HAL_CAN_GetRxFifoFillLevel(self->hcan, CAN_RX_FIFO0)) {
			CAN_get_frame(frame_1);
			recieved = 1;
		}
	}

	CAN_send_frame(frame_2);
	recieved = 0;
	while (!recieved) {
		if (HAL_CAN_GetRxFifoFillLevel(self->hcan, CAN_RX_FIFO0)) {
			CAN_get_frame(frame_2);
			recieved = 1;
		}
	}

	self->direction = (get_segment(frame_1, DRIVING_DIRECTION) >> 6);
	self->speed = get_segment(frame_1, MOTOR_SPEED);
	self->error_code = get_segment(frame_1, MOTOR_ERROR_CODE);
	self->voltage = get_segment(frame_2, BATTERY_VOLTAGE);
	self->current = get_segment(frame_2, BATTERY_CURRENT);
	self->temp = get_segment(frame_2, MOTOR_CONTROLLER_TEMP);
}

static float get_voltage(float throttle) {
  return throttle/100.0 * 5;
}
