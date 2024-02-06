/*
 * Motor_Controller.h
 *
 *  Created on: Feb 4, 2024
 *      Author: Mostafa Hussein
 */

#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include "DAC.h"
#include "telemetry.h"

struct GPIO_Pin{
	GPIO_Typedef* port;
	uint16_t pin;
};

struct MotorController {
	CAN_HandleTypeDef* hcan;

	DAC_Type* throttle;

	GPIO_Pin* fw_pin;
	GPIO_Pin* rev_pin;

	GPIO_Pin* break_sw;
};


#endif /* MOTOR_CONTROLLER_H */
