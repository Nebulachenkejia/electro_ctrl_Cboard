//
// Created by Nebula on 2025/10/12.
//

#ifndef ELECTRO_CTRL_IMU_H
#define ELECTRO_CTRL_IMU_H
#include "main.h"
#include "bmi088.h"

class IMU {
private:
    uint64_t freq_;
    float dt_;
    float x_acc_;
    float y_acc_;
    float z_acc_;
    float x_gyro_;
    float y_gyro_;
    float z_gyro_;
    float roll_;
    float pitch_;
    float yaw_;
    //滤波
    const float alpha_acc_;   // 加速度滤波系数（例如0.3）
    const float alpha_gyro_;  // 陀螺仪滤波系数（例如0.5）
    const float alpha_angle_; // 角度滤波系数（例如0.7）
    float x_acc_filtered_, y_acc_filtered_, z_acc_filtered_;
    float x_gyro_filtered_, y_gyro_filtered_, z_gyro_filtered_;
    float roll_filtered_, pitch_filtered_, yaw_filtered_;

public:
    float x_acc_raw_;
    float y_acc_raw_;
    float z_acc_raw_;
    float x_gyro_raw_;
    float y_gyro_raw_;
    float z_gyro_raw_;
    IMU(float alpha_acc, float alpha_gyro, float alpha_angle);
    void acc_calculate(uint8_t *accel_rx_data);
    void gyro_calculate(uint8_t *gyro_rx_data);
    void normalizeAngle(float& angle);
    void angle_calulate();
    float linearMapping(int32_t in, int32_t in_min, int32_t in_max, float out_min, float out_max);
    float Filter(float filter, float last_filtered, float alpha);

};


#endif //ELECTRO_CTRL_IMU_H