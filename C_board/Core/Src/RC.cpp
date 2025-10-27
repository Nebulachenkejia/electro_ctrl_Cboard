//
// Created by Nebula on 2025/10/27.
//

#include "RC.h"
void RC::init()
{
    current_time = last_time = HAL_GetTick();
}
void RC::handle(uint8_t* data, uint8_t size)
{
    if (data == nullptr || size != 18) return;

    last_time = current_time;
    rc_data_raw_.ch0 = ((int16_t)data[0] | ((int16_t)data[1] << 8)) & 0x07FF;  //取11位
    rc_data_raw_.ch1 = (((int16_t)data[1] >> 3) | ((int16_t)data[2] << 5)) & 0x07FF;    //取11位
    rc_data_raw_.ch2 = (((int16_t)data[2] >> 6) | ((int16_t)data[3] << 2) | ((int16_t)data[4] << 10)) & 0x07FF; //取11位
    rc_data_raw_.ch3 = (((int16_t)data[4] >> 1) | ((int16_t)data[5] << 7)) & 0x07FF;

    // 开关解析
    rc_data_raw_.s1 = ((data[5] >> 4) & 0x0C) >> 2;
    rc_data_raw_.s2 = (data[5] >> 4) & 0x03;

    // 鼠标与键盘解析
    rc_data_raw_.mouse_x = (int16_t)data[6] | ((int16_t)data[7] << 8);
    rc_data_raw_.mouse_y = (int16_t)data[8] | ((int16_t)data[9] << 8);
    rc_data_raw_.mouse_z = (int16_t)data[10] | ((int16_t)data[11] << 8);
    rc_data_raw_.mouse_left = data[12];
    rc_data_raw_.mouse_right = data[13];
    rc_data_raw_.key = (int16_t)data[14] | ((int16_t)data[15] << 8);
    rc_data_raw_.reserve = (int16_t)data[16] | ((int16_t)data[17] << 8);

    rc_data_.ch0 = linermapping(rc_data_raw_.ch0 ,364, 1684, -1.0f, 1.0f);
    rc_data_.ch1 = linermapping(rc_data_raw_.ch1 ,364, 1684, -1.0f, 1.0f);
    rc_data_.ch2 = linermapping(rc_data_raw_.ch2 ,364, 1684, -1.0f, 1.0f);
    rc_data_.ch3 = linermapping(rc_data_raw_.ch3 ,364, 1684, -1.0f, 1.0f);
    switch(rc_data_raw_.s1)
    {
    case 2:
        {
            rc_data_.s1 = switch_down;
            break;
        }
    case 1:
        {
            rc_data_.s1 = switch_up;
            break;
        }
    case 3:
        {
            rc_data_.s1 = switch_mid;
            break;
        }
    }
    switch(rc_data_raw_.s2)
    {
    case 2:
        {
            rc_data_.s2 = switch_down;
            break;
        }
    case 1:
        {
            rc_data_.s2 = switch_up;
            break;
        }
    case 3:
        {
            rc_data_.s2 = switch_mid;
            break;
        }
    }
}

float RC::linermapping(float x, float in_min, float in_max, float out_min, float out_max)
{
    return x * (out_max - out_min)/(in_max - in_min) + out_min;
}
