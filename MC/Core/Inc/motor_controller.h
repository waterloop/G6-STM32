/*
 * 	motor_controller.h
 *
 *  Created on: Feb 4, 2024
 *  Author: Mostafa Hussein, Mahir Mahota
 */

#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include "dac.h"
#include "can_driver.h"

#define DEFAULT_THROTTLE 100

DAC_t throttle = DAC_init(&hi2c2);
const GPIO_Pin_t FW = {.port = GPIOD, .pin = GPIO_PIN_11};
const GPIO_Pin_t REV = {.port = GPIOD, .pin = GPIO_PIN_12};
const GPIO_Pin_t BRK = {.port = GPIOD, .pin = GPIO_PIN_13};

typedef struct {
	GPIO_Typedef* port;
	uint16_t pin;
} GPIO_Pin_t;

typedef struct {
	CAN_HandleTypeDef* hcan;
	uint8_t direction;
	uint16_t speed;
	uint8_t error_code;
	uint16_t voltage;
	uint16_t current;
	uint16_t temp;
} Motor_Controller_Data_t;

Motor_Controller_t MC_init(CAN_HandleTypeDef* handler);
void MC_stop(void);
void MC_drive(void);
void MC_change_direction(void);
void MC_set_throttle(float throttle);
uint8_t MC_get_data(Motor_Controller_Data_t* self);

static float get_voltage(float throttle);

#endif /* MOTOR_CONTROLLER_H */
