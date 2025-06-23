#include "uart_cmd.h"
#include <ctype.h>

uint8_t rx_buffer[UART_RX_BUFFER_SIZE];

/**
 * @brief 处理接收到的命令
 * @param cmd 接收到的命令字符串
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (UART_DEBUG) {
        if (rx_byte == ':')
            rx_index = 0;
        else if (rx_index >= 0) {
            if (rx_byte == ';') {
                rx_buffer[rx_index ++] = rx_byte;
                rx_index = -1;  // 重置索引
                process_cmd(rx_buffer);
            } else if (rx_byte != '\n' && rx_byte != '\r') {
                rx_buffer[rx_index ++] = rx_byte;
            }
        }
        HAL_UART_Receive_IT(&hlpuart1, (uint8_t *) &rx_byte, 1);
    }
}

void process_cmd(uint8_t *rx_buffer) {
    char cmd[10];
    char param;
    float value;

    char str[40];
    sprintf(str, "CMD: %s\r\n", (char *) rx_buffer);
    HAL_UART_Transmit(&hlpuart1, str, strlen(str), HAL_MAX_DELAY);

    /* 解析命令 */
    char value_str[10];
    int parsed = sscanf((char*) rx_buffer, "%3s %c %s", cmd, &param, value_str);

    if (parsed == 3 && strcmp(cmd, "SET") == 0) {
        value = strtod(value_str, ";");
        /* 设置 PID 参数 */
        switch(param) {
            case 'P':
                motor_l_speed_pid.kp = value;
                motor_r_speed_pid.kp = value;
                break;
            case 'I':
                motor_l_speed_pid.ki = value;
                motor_r_speed_pid.ki = value;
                break;
            case 'D':
                motor_l_speed_pid.kd = value;
                motor_r_speed_pid.kd = value;
                break;
            case 'p':
                motor_l_position_pid.kp = value;
                motor_r_position_pid.kp = value;
                break;
            case 'i':
                motor_l_position_pid.ki = value;
                motor_r_position_pid.ki = value;
                break;
            case 'd':
                motor_l_position_pid.kd = value;
                motor_r_position_pid.kd = value;
                break;
            case 'R':
            case 'r':
                HAL_UART_Transmit(&hlpuart1, (uint8_t*)"Reset!\r\n", 8, HAL_MAX_DELAY);
                motor_init();
                break;
            case 'M':
            case 'm':
                motor_set_position(value, value,  100);
                MOTOR_ENABLE();
                break;
            default:
                // 无效参数
                HAL_UART_Transmit(&hlpuart1, (uint8_t*)"ERROR: Invalid parameter\r\n", 26, HAL_MAX_DELAY);
                return;
        }

        // 确认设置
        // char response[64];
        // snprintf(response, sizeof(response), "OK: %c set to %.4f\r\n", toupper(param), value);
        // HAL_UART_Transmit(&hlpuart1, (uint8_t *) response, strlen(response), HAL_MAX_DELAY);
    } else {
        // 无效命令
        // HAL_UART_Transmit(&hlpuart1, (uint8_t*)"ERROR: Invalid command format\r\n", 30, HAL_MAX_DELAY);
    }
}