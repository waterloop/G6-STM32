/*
 * 	motor_controller.h
 *
 *  Created on: Feb 4, 2024
 *  Author: Mahir Mahota
 */

#include "motor_controller.h"
#include "config.h"

const GPIO_Pin_t FW = {.port = GPIOD, .pin = GPIO_PIN_11};
const GPIO_Pin_t REV = {.port = GPIOD, .pin = GPIO_PIN_12};
const GPIO_Pin_t BRK = {.port = GPIOD, .pin = GPIO_PIN_13};

Motor_Controller_t MC_init(CAN_HandleTypeDef* handler, I2C_HandleTypeDef* i2c_handler) {
	Motor_Controller_t ret = {
		.hcan = handler,
		.direction = 0,
		.speed = 0,
		.error_code = 0,
		.voltage = 0,
		.current = 0,
		.temp = 0,
		.throttle = DAC_init(i2c_handler)
	};

	return ret;
}

void MC_stop(Motor_Controller_t* self) {
	DAC_write(self -> throttle, 0);
	HAL_GPIO_WritePin(BRK.port, BRK.pin, GPIO_PIN_SET);
}

void MC_drive(Motor_Controller_t* self) {
	HAL_GPIO_WritePin(BRK.port, BRK.pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(REV.port, REV.pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(FW.port, FW.pin, GPIO_PIN_SET);
	DAC_write(self -> throttle, get_voltage(DEFAULT_THROTTLE));
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

void MC_set_throttle(Motor_Controller_t* self, float value) {
	DAC_write(self -> throttle, get_voltage(value));
}

void MC_get_data(Motor_Controller_t* self) {

	CAN_Frame_t frame_1 = CAN_frame_init(self->hcan, MOTOR_CONTROLLER_K1);
	CAN_Frame_t frame_2 = CAN_frame_init(self->hcan, MOTOR_CONTROLLER_K2);
	frame_1.id_type = CAN_ID_EXT;
	frame_1.data_length = 0;
	frame_2.id_type = CAN_ID_EXT;
	frame_2.data_length = 0;

	CAN_send_frame(frame_1);
	uint8_t recieved = 0;
	while (!recieved) {
		if (HAL_CAN_GetRxFifoFillLevel(self->hcan, CAN_RX_FIFO0)) {
			frame_1 = CAN_get_frame(self->hcan, CAN_RX_FIFO0);
			recieved = 1;
		}
	}

	CAN_send_frame(frame_2);
	recieved = 0;
	while (!recieved) {
		if (HAL_CAN_GetRxFifoFillLevel(self->hcan, CAN_RX_FIFO0)) {
			frame_2 = CAN_get_frame(self->hcan, CAN_RX_FIFO0);
			recieved = 1;
		}
	}

	self->direction = (CAN_get_segment(frame_1, DRIVING_DIRECTION) >> 6);
	self->speed = CAN_get_segment(frame_1, MOTOR_SPEED);
	self->error_code = CAN_get_segment(frame_1, MOTOR_ERROR_CODE);
	self->voltage = CAN_get_segment(frame_2, BATTERY_VOLTAGE);
	self->current = CAN_get_segment(frame_2, BATTERY_CURRENT);
	self->temp = CAN_get_segment(frame_2, MOTOR_CONTROLLER_TEMP);
}

float get_voltage(float throttle) {
  return throttle/100.0 * 5;
}

void MC_execute_command(CAN_Frame_t frame) {

}
