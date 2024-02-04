/*
 * Motor_Controller.h
 *
 *  Created on: Feb 4, 2024
 *      Author: Mostafa Hussein
 */

#ifndef DAC_H
#define DAC_H

#include "i2c.h"

struct DAC_Type {
	I2C_HandleTypeDef* hi2c;
};


#endif /* DAC_H */
