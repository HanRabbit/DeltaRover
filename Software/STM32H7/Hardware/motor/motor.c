#include "motor.h"
#include <stdlib.h>

__IO int32_t encoder1_speed = 0;
__IO int32_t encoder2_speed = 0;

PID_t motor_l_pid;
PID_t motor_r_pid;

void motor_init(void) {
    pid_init(&motor_l_pid, 0.01f, 0.1f, 0.001f, 0.01f); // 初始化左电机 PID 速度控制器
    pid_init(&motor_r_pid, 0.01f, 0.1f, 0.001f, 0.01f); // 初始化右电机 PID 速度控制器
    motor_l_pid.mode = PID_MODE_SPEED; // 设置左电机为速度控制模式
    motor_r_pid.mode = PID_MODE_SPEED; // 设置右电机为速度控制模式
}

void motor_l_set_speed(const int32_t speed) {
    motor_l_pid.target_speed = (float) speed;
}

void motor_r_set_speed(const int32_t speed) {
    motor_r_pid.target_speed = (float) speed;
}

void motor_set_speed(const int32_t l_speed, const int32_t r_speed) {
    motor_l_set_speed(l_speed);
    motor_r_set_speed(r_speed);
}

void motor_update(void) {
    MOTOR_L_PWM((int32_t) pid_update(&motor_l_pid, (float) encoder1_speed));
    MOTOR_R_PWM((int32_t) pid_update(&motor_r_pid, (float) encoder2_speed));
}
