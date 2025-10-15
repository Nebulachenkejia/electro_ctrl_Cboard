//
// Created by Nebula on 2025/10/12.
//

#ifndef ELECTRO_CTRL_IMU088_H
#define ELECTRO_CTRL_IMU088_H
#ifdef __cplusplus  // 仅在C++编译时生效（区分C/C++编译器）
extern "C" {
#endif
#include "main.h"

//用于片选
void BMI088_ACCEL_NS_L(void);
void BMI088_ACCEL_NS_H(void);
void BMI088_GYRO_NS_L(void);
void BMI088_GYRO_NS_H(void);

//底层通信函数
void bmi088_write_byte(uint8_t tx_data);
void bmi088_read_byte(uint8_t *rx_data, uint8_t length);
//专用设备操作函数
void bmi088_accel_write_single_reg(uint8_t reg, uint8_t data);
void bmi088_accel_read_reg(uint8_t reg, uint8_t *rx_data, uint8_t length); // 加速度计读取，注意需要忽略第一位数据dummy byte
void bmi088_gyro_read_reg(uint8_t reg, uint8_t *rx_data, uint8_t length);// 陀螺仪读取
void bmi088_gyro_write_single_reg(uint8_t reg, uint8_t data);

//用于修改配置
void bmi088_write_reg(uint8_t reg, uint8_t data);

//用于初始化
void bmi088_init(void);

#ifdef __cplusplus  // 仅在C++编译时生效（区分C/C++编译器）
}
#endif

#endif //ELECTRO_CTRL_IMU088_H


//待优化：寄存器地址使用宏定义；函数操作判断可以添加返回值；设备ID宏定义；函数体参数检查