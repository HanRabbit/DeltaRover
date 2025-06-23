#include "sys_info.h"

char rx_byte;
int8_t rx_index = -1;

void sys_init() {
    HAL_UART_Receive_IT(&hlpuart1, (uint8_t *) &rx_byte, 1);

    HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1);

    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    /* 启动编码器速度读取定时器中断 */
    HAL_TIM_Base_Start_IT(&htim6);

    /* 启动电机状态刷新定时器中断 */
    HAL_TIM_Base_Start_IT(&htim14);

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
    if (OLED_STATUS_PRINT) {
        char speed1_str[16];
        snprintf(speed1_str, sizeof(speed1_str), "L_POS: %d      ", motor_l_position);
        OLED_ShowString(6, 1, speed1_str, 12, 0);
        char speed2_str[16];
        snprintf(speed2_str, sizeof(speed2_str), "R_POS: %d      ", motor_r_position);
        OLED_ShowString(6, 3, speed2_str, 12, 0);
        char output1_str[16];
        snprintf(output1_str, sizeof(output1_str), "OUT_A: %d      ", (int32_t) motor_l_speed_pid.output);
        OLED_ShowString(6, 5, output1_str, 12, 0);
        char output2_str[16];
        snprintf(output2_str, sizeof(output2_str), "OUT_B: %d      ", (int32_t) motor_r_speed_pid.output);
        OLED_ShowString(6, 7, output2_str, 12, 0);

        // char PID_P_str[16];
        // snprintf(PID_P_str, sizeof(PID_P_str), "P: %.3f", motor_l_speed_pid.kp);
        // OLED_ShowString(6, 1, PID_P_str, 12, 0);
        // char PID_I_str[16];
        // snprintf(PID_I_str, sizeof(PID_I_str), "I: %.3f", motor_l_speed_pid.ki);
        // OLED_ShowString(6, 3, PID_I_str, 12, 0);
        // char PID_D_str[16];
        // snprintf(PID_D_str, sizeof(PID_D_str), "D: %.3f", motor_l_speed_pid.kd);
        // OLED_ShowString(6, 5, PID_D_str, 12, 0);
    }

    if (UART_STATUS_PRINT) {
        printf("ENC_A=%d,ENC_B=%d,OUT_A=%d,OUT_B=%d,L_POS=%d,R_POS=%d\n", encoder1_speed, encoder2_speed,
        (int32_t) motor_l_speed_pid.output, (int32_t) motor_r_speed_pid.output,(int32_t) motor_l_position, (int32_t) motor_r_position);
    }
}
