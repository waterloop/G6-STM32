#include "mpu6050.h"
#include "i2c.h" // You may need to include this for hi2c1

static I2C_HandleTypeDef i2c_handler;

float MPU6050_Read_Accel(char axis){
	uint8_t Rec_Data[6];
	HAL_I2C_Mem_Read(&i2c_handler, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, Rec_Data, 6, 1000);

	switch(axis){
	case 'x':
		int16_t Accel_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
		float Ax = Accel_X_RAW / 16384.0;
		return Ax;

	case 'y':
		int16_t Accel_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
		float Ay = Accel_Y_RAW / 16384.0;
		return Ay;


	case 'z': //most likely won't need
		int16_t Accel_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);
		float Az = Accel_Z_RAW / 16384.0;
		return Az;


	}
}

float MPU6050_Read_Gyro(char axis){
    uint8_t Rec_Data[6];
    HAL_I2C_Mem_Read(&i2c_handler, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, Rec_Data, 6, 1000);

	switch(axis){
	case 'x':
		int16_t Gyro_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
		float Gx = Gyro_X_RAW / 131.0;
		return Gx;

	case 'y':
		int16_t Gyro_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
		float Gy = Gyro_X_RAW / 131.0;
		return Gy;


	case 'z': //most likely won't need
		int16_t Gyro_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);
		float Gz = Gyro_X_RAW / 131.0;
		return Gz;
	}
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
