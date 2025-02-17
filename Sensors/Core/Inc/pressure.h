/*
 * pressure.h
 *
 *  Created on: Apr 25, 2024
 *      Author: mahesh, mahir
 */

#ifndef INC_PRESSURE_H_
#define INC_PRESSURE_H_

#include <stdint.h>
#define MAX_ADC_VALUE 4095
#define MAX_VOLTS 3.3

uint8_t volts_to_psi (uint8_t volts);
uint8_t poll_pressure_sensor(void);

#endif /* INC_PRESSURE_H_ */
