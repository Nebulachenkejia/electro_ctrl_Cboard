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
    float roll;
    float pitch;
    float yaw;

public:
    float x_acc_raw_;
    float y_acc_raw_;
    float z_acc_raw_;
    float x_gyro_raw_;
    float y_gyro_raw_;
    float z_gyro_raw_;
    IMU();
    void acc_calculate(uint8_t *accel_rx_data);
    void gyro_calculate(uint8_t *gyro_rx_data);
    float linearMapping(int in, int in_min, int in_max, int out_min, int out_max);

};


#endif //ELECTRO_CTRL_IMU_H