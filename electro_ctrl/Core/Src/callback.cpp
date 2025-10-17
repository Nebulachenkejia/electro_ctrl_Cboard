//
// Created by Nebula on 2025/10/15.
//


#include "IMU.h"
#include "tim.h"

IMU imu(0.3,0.3,0.7);
extern uint8_t accel_rx_data[6];
extern uint8_t gyro_rx_data[6];

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim -> Instance == htim6.Instance)
    {
        //加速度计
        BMI088_GYRO_NS_H();
        BMI088_ACCEL_NS_L();
        bmi088_accel_read_reg(0x12, accel_rx_data, 6);  // 阻塞读取
        imu.acc_calculate(accel_rx_data);
        //陀螺仪
        BMI088_ACCEL_NS_H();
        BMI088_GYRO_NS_L();
        bmi088_gyro_read_reg(0x02, gyro_rx_data, 6);    // 阻塞读取
        BMI088_GYRO_NS_H();
        imu.gyro_calculate(gyro_rx_data);
        imu.angle_calulate();

    }
}