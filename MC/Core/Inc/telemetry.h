/*
 * telemetry.h
 *
 *  Created on: Feb 4, 2024
 *      Author: Mostafa Hussein
 */

#ifndef TELEMETRY_H
#define TELEMETRY_H

#include "usart.h"


struct Telemetry_Type {
	UART_HandleTypeDef* huart;
};


#endif /* TELEMETRY_H */
