//
// Created by Nebula on 2025/10/27.
//

#ifndef C_BOARD_RC_H
#define C_BOARD_RC_H
#include "main.h"
#define USART3_RX_BUF_SIZE 32
#define USART3_RX_DATA_SIZE 32
class RC
{
private:
    typedef enum {switch_up = 0, switch_down = 1, switch_mid = 2} Switch_state;
    struct RC_data_Raw
    {
        // 4个通道
        uint16_t ch0;  // 通道0
        uint16_t ch1;  // 通道1
        uint16_t ch2;  // 通道2
        uint16_t ch3;  // 通道3

        // 2个开关
        uint8_t s1;    // S1开关
        uint8_t s2;    // S2开关

        // 鼠标数据
        int16_t mouse_x;  // X轴
        int16_t mouse_y;  // Y轴
        int16_t mouse_z;  // Z轴

        // 鼠标
        uint8_t mouse_left;  // 左键
        uint8_t mouse_right; // 右键

        // 键盘按键
        uint16_t key;

        // 保留字段
        uint16_t reserve;

        RC_data_Raw()
        {
            ch0 = ch1 = ch2 = ch3 = 1024;
            s1 = s2 = 3;
            mouse_x = mouse_y = mouse_z = 0;
            mouse_left = mouse_right = 0;
            key = 0;
            reserve = 0;
        }
    } __packed rc_data_raw_;

    struct RC_data
    {
        // 4个通道
        float ch0;  // 通道0
        float ch1;  // 通道1
        float ch2;  // 通道2
        float ch3;  // 通道3

        // 2个开关
        Switch_state s1;    // S1开关
        Switch_state s2;    // S2开关

        RC_data()
        {
            ch0 = ch1 = ch2 = ch3 = 0.0f;
            s1 = s2 = switch_down;
        }
    } __packed rc_data_;



public:
    RC(){};
    void init();
    void handle(uint8_t* data, uint8_t size);
    bool isConnected = false;
    uint64_t last_time = 0;
    uint64_t current_time = 0;
    float linermapping(float x, float in_min, float in_max, float out_min, float out_max);
};


#endif //C_BOARD_RC_H