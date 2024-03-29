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

void MPU6050_Init(void);
float MPU6050_Read_Accel(char axis, I2C_HandleTypeDef i2c);
float MPU6050_Read_Gyro(char axis, I2C_HandleTypeDef i2c);
