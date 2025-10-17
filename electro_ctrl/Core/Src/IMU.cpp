//
// Created by Nebula on 2025/10/12.
//

#include "IMU.h"
#define g (9.81)
#define GYRO_SCALE_FACTOR  (2000.0f / 32768.0f)

IMU::IMU(float alpha_acc, float alpha_gyro, float alpha_angle)
    : alpha_acc_(alpha_acc), alpha_gyro_(alpha_gyro), alpha_angle_(alpha_angle){
    freq_ = 1000;
    dt_ = 0.001;
    x_acc_ = 0.0;
    y_acc_ = 0.0;
    z_acc_ = 0.0;
    x_acc_raw_ = 0.0;
    y_acc_raw_ = 0.0;
    z_acc_raw_ = 0.0;
    x_gyro_ = 0.0;
    y_gyro_ = 0.0;
    z_gyro_ = 0.0;
    x_gyro_raw_ = 0.0;
    y_gyro_raw_ = 0.0;
    z_gyro_raw_ = 0.0;
    roll_ = 0.0;
    pitch_ = 0.0;
    yaw_ = 0.0;
}

float IMU::linearMapping(int32_t in, int32_t in_min, int32_t in_max, float out_min, float out_max)
{
    return (in - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float IMU::Filter(float filter, float last_filtered, float alpha)
{
    return alpha * filter + (1 - alpha) * last_filtered;
}

void IMU::normalizeAngle(float& angle){
    while(angle > 180.0)    { angle-=360.0f; }
    while(angle < -180.0)   { angle+=360.0f; }
}

void IMU::acc_calculate(uint8_t* accel_rx_data)
{
    x_acc_raw_ = (accel_rx_data[1] << 8) | accel_rx_data[0];
    y_acc_raw_ = (accel_rx_data[3] << 8) | accel_rx_data[2];
    z_acc_raw_ = (accel_rx_data[5] << 8) | accel_rx_data[4];
    x_acc_ = linearMapping(x_acc_raw_, -32768, 32768, -6*g,6*g);
    y_acc_ = linearMapping(y_acc_raw_, -32768, 32768, -6*g,6*g);
    z_acc_ = linearMapping(z_acc_raw_, -32768, 32768, -6*g,6*g);
    if (x_acc_filtered_==0.0f)
    {
        x_acc_filtered_ = x_acc_;
        y_acc_filtered_ = y_acc_;
        z_acc_filtered_ = z_acc_;
    }
    else
    {
        Filter(x_acc_, x_acc_filtered_, alpha_acc_);
        Filter(y_acc_, y_acc_filtered_, alpha_acc_);
        Filter(z_acc_, z_acc_filtered_, alpha_acc_);
    }
}

void IMU::gyro_calculate(uint8_t *gyro_rx_data)
{
    x_gyro_raw_ = (gyro_rx_data[1] << 8) | gyro_rx_data[0];
    y_gyro_raw_ = (gyro_rx_data[3] << 8) | gyro_rx_data[2];
    z_gyro_raw_ = (gyro_rx_data[5] << 8) | gyro_rx_data[4];
    x_gyro_ = x_gyro_raw_ * GYRO_SCALE_FACTOR;
    y_gyro_ = y_gyro_raw_ * GYRO_SCALE_FACTOR;
    z_gyro_ = z_gyro_raw_ * GYRO_SCALE_FACTOR;
    if (x_gyro_filtered_==0.0f)
    {
        x_gyro_filtered_ = x_gyro_;
        y_gyro_filtered_ = y_gyro_;
        z_gyro_filtered_ = z_gyro_;
    }
    else
    {
        Filter(x_gyro_, x_gyro_filtered_, alpha_gyro_);
        Filter(y_gyro_, y_gyro_filtered_, alpha_gyro_);
        Filter(z_gyro_, z_gyro_filtered_, alpha_gyro_);
    }
}

void IMU::angle_calulate()
{
    roll_ += x_gyro_ * dt_;
    pitch_ += y_gyro_ * dt_;
    yaw_ += z_gyro_ * dt_;
    if (roll_filtered_==0.0f)
    {
        roll_filtered_ = roll_;
        pitch_filtered_ = pitch_;
        yaw_filtered_ = yaw_;
    }
    else
    {
        Filter(roll_,roll_filtered_,alpha_angle_);
        Filter(pitch_, pitch_filtered_, alpha_angle_);
        Filter(yaw_, yaw_filtered_, alpha_angle_);
    }

    normalizeAngle(roll_);
    normalizeAngle(pitch_);
    normalizeAngle(yaw_);
}