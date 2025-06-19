#include "uart_cmd.h"
#include <ctype.h>

/**
 * @brief 处理接收到的命令
 * @param cmd 接收到的命令字符串
 */
void HAL_UART_RxCpltCallback(const UART_HandleTypeDef *huart) {
    if (huart == &hlpuart1 && UART_DEBUG) {
        if (uart_rx_buffer[uart_rx_index] == ';' || uart_rx_index >= UART_RX_BUFFER_SIZE - 1) {
            if (uart_rx_buffer[uart_rx_index] != ';') {
                uart_rx_buffer[uart_rx_index + 1] = '\0'; // 确保字符串终止
            } else {
                uart_rx_buffer[uart_rx_index] = '\0'; // 替换分号为字符串终止符
            }

            process_cmd(uart_rx_buffer);
            uart_rx_index = 0;
        } else {
            uart_rx_index ++;
        }

        // 重新开始接收
        HAL_UART_Receive_IT(&hlpuart1, (uint8_t *) &uart_rx_buffer[uart_rx_index], 1);
    }
}

void process_cmd(uint8_t *rx_buffer) {
    char cmd[10];
    char param;
    float value;

    /* 解析命令 */
    int parsed = sscanf(cmd, "%s %c %f", cmd, &param, &value);

    if (parsed == 3 && strcmp(cmd, "SET") == 0) {
        /* 设置 PID 参数 */
        switch(param) {
            case 'P':
            case 'p':
                motor_l_speed_pid.kp = value;
                motor_r_speed_pid.kp = value;
                break;
            case 'I':
            case 'i':
                motor_l_speed_pid.ki = value;
                motor_r_speed_pid.ki = value;
                break;
            case 'D':
            case 'd':
                motor_l_speed_pid.kd = value;
                motor_r_speed_pid.kd = value;
                break;
            default:
                // 无效参数
                HAL_UART_Transmit(&hlpuart1, (uint8_t*)"ERROR: Invalid parameter\r\n", 26, HAL_MAX_DELAY);
                return;
        }

        // 确认设置
        char response[64];
        snprintf(response, sizeof(response), "OK: %c set to %.4f\r\n", toupper(param), value);
        HAL_UART_Transmit(&hlpuart1, (uint8_t*)response, strlen(response), HAL_MAX_DELAY);
    } else {
        // 无效命令
        HAL_UART_Transmit(&hlpuart1, (uint8_t*)"ERROR: Invalid command format\r\n", 30, HAL_MAX_DELAY);
        HAL_UART_Transmit(&hlpuart1, (uint8_t*)"Usage:\r\n", 8, HAL_MAX_DELAY);
        HAL_UART_Transmit(&hlpuart1, (uint8_t*)"  SET P 0.001; - Set P parameter\r\n", 32, HAL_MAX_DELAY);
        HAL_UART_Transmit(&hlpuart1, (uint8_t*)"  SET I 0.0001; - Set I parameter\r\n", 33, HAL_MAX_DELAY);
        HAL_UART_Transmit(&hlpuart1, (uint8_t*)"  SET D 0.01; - Set D parameter\r\n", 31, HAL_MAX_DELAY);
        HAL_UART_Transmit(&hlpuart1, (uint8_t*)"  GET; - Get current PID values\r\n", 32, HAL_MAX_DELAY);
    }
}