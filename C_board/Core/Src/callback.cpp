//
// Created by Nebula on 2025/10/26.
//
#include "main.h"
#include <cstring>
#include "RC.h"
#define USART3_RX_BUF_SIZE 32
#define USART3_RX_DATA_SIZE 32
#define RC_DATA_SIZE 18
extern UART_HandleTypeDef huart3;
extern uint64_t msg_time;
extern uint8_t rx_buf[USART3_RX_BUF_SIZE];
extern uint8_t rx_data[USART3_RX_DATA_SIZE];
RC rc;

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if (huart->Instance == huart3.Instance)
    {
        static bool rc_inited = false;
        if (!rc_inited)
        {
            rc.init();
            rc_inited = true;
        }
        rc.current_time = HAL_GetTick();
        rc.isConnected =  (rc.current_time - rc.last_time) < 100;
        memcpy(rx_data, rx_buf, Size);
        rc.handle(rx_data, Size);
        HAL_UARTEx_ReceiveToIdle_DMA(&huart3, rx_buf, USART3_RX_BUF_SIZE);
    }
}