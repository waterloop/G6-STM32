/*
 * 	motor_controller.h
 *
 *  Created on: Feb 4, 2024
 *  Author: Mostafa Hussein, Mahir Mahota
 */

#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include "motor_controller.h"
#include "can_driver.h"
#include "gpio.h"
#include "dac.h"

#define DEFAULT_THROTTLE 100

typedef struct {
	GPIO_TypeDef* port;
	uint16_t pin;
} GPIO_Pin_t;

typedef struct {
	CAN_HandleTypeDef* hcan;
	DAC_t throttle;
	uint8_t direction;
	uint16_t speed;
	uint8_t error_code;
	uint16_t voltage;
	uint16_t current;
	uint16_t temp;
} Motor_Controller_t;

Motor_Controller_t MC_init(CAN_HandleTypeDef* can_handler, I2C_HandleTypeDef* i2c_handler);
void MC_stop(Motor_Controller_t* self);
void MC_drive(Motor_Controller_t* self);
void MC_change_direction(void);
void MC_set_throttle(Motor_Controller_t* self, float value);
void MC_get_data(Motor_Controller_t* self);
void MC_execute_command(CAN_Frame_t frame);

float get_voltage(float throttle);

#endif /* MOTOR_CONTROLLER_H */
