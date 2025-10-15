//
// Created by Nebula on 2025/10/12.
//

#include "IMU.h"
#define g (9.81)
#define GYRO_SCALE_FACTOR  (2000.0f / 32768.0f)

IMU::IMU(){
    freq_ = 1000;
    dt_ = 1/freq_;
    x_acc_ = 0.0;
    y_acc_ = 0.0;
    z_acc_ = 0.0;
    x_gyro_ = 0.0;
    y_gyro_ = 0.0;
    z_gyro_ = 0.0;
    roll = 0.0;
    pitch = 0.0;
    yaw = 0.0;
}

float IMU::linearMapping(int in, int in_min, int in_max, int out_min, int out_max)
{
    return (in - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void IMU::acc_calculate(uint8_t* accel_rx_data)
{
    x_acc_raw_ = (accel_rx_data[1] << 8) | accel_rx_data[0];
    y_acc_raw_ = (accel_rx_data[3] << 8) | accel_rx_data[2];
    z_acc_raw_ = (accel_rx_data[5] << 8) | accel_rx_data[4];
    x_acc_ = linearMapping(x_acc_raw_, -32768, 32768, -6*g,6*g);
    y_acc_ = linearMapping(y_acc_raw_, -32768, 32768, -6*g,6*g);
    z_acc_ = linearMapping(z_acc_raw_, -32768, 32768, -6*g,6*g);
}

void IMU::gyro_calculate(uint8_t *gyro_rx_data)
{
    x_gyro_raw_ = (gyro_rx_data[1] << 8) | gyro_rx_data[0];
    y_gyro_raw_ = (gyro_rx_data[3] << 8) | gyro_rx_data[2];
    z_gyro_raw_ = (gyro_rx_data[5] << 8) | gyro_rx_data[4];
    x_gyro_ = x_gyro_raw_ * GYRO_SCALE_FACTOR;
    y_gyro_ = y_gyro_raw_ * GYRO_SCALE_FACTOR;
    z_gyro_ = z_gyro_raw_ * GYRO_SCALE_FACTOR;

}

