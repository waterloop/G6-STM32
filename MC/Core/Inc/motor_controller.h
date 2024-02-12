/*
 * Motor_Controller.h
 *
 *  Created on: Feb 4, 2024
 *      Author: Mostafa Hussein
 */

#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include "DAC.h"
// #include "can_driver.h"

typedef struct{
	GPIO_Typedef* port;
	uint16_t pin;
} GPIO_Pin_t ;

typedef struct {
	CAN_HandleTypeDef* hcan;
	// TODO: Replace the hcan with CANFrame
	// CANFrame can_frame;

	DAC_Type* throttle;

	GPIO_Pin* fw_pin;
	GPIO_Pin* rev_pin;

	GPIO_Pin* break_sw;
} Motor_Controller_t;

Motor_Controller_t MC_Init(
	CAN_HandleTypeDef* hcan,
	// TODO: Replace the hcan with the CANFrame
	// CANFrame can_frame,
	DAC_Type* throttle_dac,
	GPIO_Pin* forward_pin,
	GPIO_Pin* reverse_pin,
	GPIO_Pin* break_sw_pin
);

void MC_stop(Motor_Controller_t* MC);
void MC_drive(Motor_Controller_t* MC);
void MC_set_throttle(Motor_Controller_t* MC, float throttle);
void MC_get_telem(Motor_Controller_t* MC);

static float get_voltage(float throttle);

#endif /* MOTOR_CONTROLLER_H */
