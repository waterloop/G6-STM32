#pragma once
#include "stm32f7xx_hal.h"

#define MPU6050_ADDR        0x68
#define ACCEL_XOUT_H_REG    0x3B
#define GYRO_XOUT_H_REG     0x43
#define WHO_AM_I_REG        0x75
#define PWR_MGMT_1_REG      0x6B
#define SMPLRT_DIV_REG      0x19
#define ACCEL_CONFIG_REG    0x1C
#define GYRO_CONFIG_REG     0x1B

void MPU6050_Init(I2C_HandleTypeDef hi2c);
void MPU6050_Read_Accel(int8_t* x_accel, int8_t* y_accel);
void MPU6050_Read_Gyro(int8_t* x_gyro, int8_t* y_gyro, int8_t* z_gyro);
