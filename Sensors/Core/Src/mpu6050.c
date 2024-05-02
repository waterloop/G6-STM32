#include "mpu6050.h"
#include "i2c.h" // You may need to include this for hi2c1
#include <stdio.h>

static I2C_HandleTypeDef i2c_handler;

void MPU6050_Read_Accel(int8_t* x_accel, int8_t* y_accel){
	uint8_t Rec_Data[6];
	HAL_I2C_Mem_Read(&i2c_handler, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, Rec_Data, 6, 1000);
//	printf("%d, ", Rec_Data[0]);
//	printf("%d, ", Rec_Data[1]);
//	printf("%d, ", Rec_Data[2]);
//	printf("%d, ", Rec_Data[3]);
//	printf("%d, ", Rec_Data[4]);
//	printf("%d, \n", Rec_Data[5]);


	int16_t Accel_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
	*x_accel = (Accel_X_RAW / 16384.0);

	int16_t Accel_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
	*y_accel = Accel_Y_RAW / 16384.0;
}

void MPU6050_Read_Gyro(int8_t* x_gyro, int8_t* y_gyro, int8_t* z_gyro){
    uint8_t Rec_Data[6];
    HAL_I2C_Mem_Read(&i2c_handler, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, Rec_Data, 6, 1000);

	int16_t Gyro_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
	*x_gyro = Gyro_X_RAW / 131.0;

	int16_t Gyro_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
	*y_gyro = Gyro_Y_RAW / 131.0;

	int16_t Gyro_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);
	*z_gyro = Gyro_Z_RAW / 131.0;
}



void MPU6050_Init (I2C_HandleTypeDef hi2c){
    uint8_t check, data;
    i2c_handler = hi2c;
    HAL_I2C_Mem_Read(&i2c_handler, MPU6050_ADDR, WHO_AM_I_REG, 1, &check, 1, 1000);

    if (check == 104){
        data = 0;
        HAL_I2C_Mem_Write(&i2c_handler, MPU6050_ADDR, PWR_MGMT_1_REG, 1, &data, 1, 1000);
        data = 0x07;
        HAL_I2C_Mem_Write(&i2c_handler, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &data, 1, 1000);

        data = 0x00;
        HAL_I2C_Mem_Write(&i2c_handler, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &data, 1, 1000);

        data = 0x00;
        HAL_I2C_Mem_Write(&i2c_handler, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &data, 1, 1000);
    }
}
