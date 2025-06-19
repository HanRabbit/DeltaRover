#include "sys_info.h"

void sys_init() {
    HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1);

    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    /* 启动编码器速度读取定时器中断 */
    HAL_TIM_Base_Start_IT(&htim6);

    /* OLED 显示屏初始化 */
    OLED_Init();
    OLED_Clear();

    /* 启动 OLED 显示定时器中断 */
    HAL_TIM_Base_Start_IT(&htim13);

    BUZZER_TOGGLE(30);
    HAL_Delay(50);
    BUZZER_TOGGLE(30);

    MOTOR_ENABLE();
    motor_init();
}

void sys_info_update(void) {
    char speed1_str[16];
    snprintf(speed1_str, sizeof(speed1_str), "ENC_A: %d    ", encoder1_speed);
    OLED_ShowString(6, 1, speed1_str, 12, 0);
    char speed2_str[16];
    snprintf(speed2_str, sizeof(speed2_str), "ENC_B: %d    ", encoder2_speed);
    OLED_ShowString(6, 3, speed2_str, 12, 0);
    char output1_str[16];
    snprintf(output1_str, sizeof(output1_str), "OUT_A: %d    ", (int32_t) motor_l_speed_pid.output);
    OLED_ShowString(6, 5, output1_str, 12, 0);
    char output2_str[16];
    snprintf(output2_str, sizeof(output2_str), "OUT_B: %d    ", (int32_t) motor_r_speed_pid.output);
    OLED_ShowString(6, 7, output2_str, 12, 0);

    char uart_msg[40];
    snprintf(uart_msg, sizeof(uart_msg), "ENC_A=%d,ENC_B=%d,OUT_A=%d,OUT_B=%d,", encoder1_speed, encoder2_speed,
             (int32_t) motor_l_speed_pid.output, (int32_t) motor_r_speed_pid.output);
    HAL_UART_Transmit(&hlpuart1, (uint8_t *) uart_msg, strlen(uart_msg), HAL_MAX_DELAY);
}