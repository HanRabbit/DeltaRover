#include "motor.h"
#include <stdlib.h>

__IO int32_t encoder1_speed = 0;
__IO int32_t encoder2_speed = 0;

PID_t motor_l_speed_pid;
PID_t motor_r_speed_pid;
PID_t motor_l_position_pid;
PID_t motor_r_position_pid;

void motor_init(void) {
    /* 电机速度环控制器初始化 */
    pid_init(&motor_l_speed_pid, 0.01f, 0.1f, 0.001f, 0.01f);
    pid_init(&motor_r_speed_pid, 0.01f, 0.1f, 0.001f, 0.01f);
    pid_set_mode(&motor_l_speed_pid, PID_MODE_SPEED);
    pid_set_mode(&motor_r_speed_pid, PID_MODE_SPEED);

    /* 电机位置环控制器初始化 */
    pid_init(&motor_l_position_pid, 0.01f, 0.1f, 0.001f, 0.01f);
    pid_init(&motor_r_position_pid, 0.01f, 0.1f, 0.001f, 0.01f);
}

void motor_l_set_speed(const int32_t speed) { motor_l_speed_pid.target = (float) speed; }
void motor_r_set_speed(const int32_t speed) { motor_r_speed_pid.target = (float) speed; }

void motor_set_speed(const int32_t l_speed, const int32_t r_speed) {
    motor_l_set_speed(l_speed);
    motor_r_set_speed(r_speed);
}

void motor_set_position(const int32_t l_pos, const int32_t r_pos) {
    motor_l_position_pid.target = (float) l_pos;
    motor_r_position_pid.target = (float) r_pos;
}

void motor_update(void) {
    MOTOR_L_PWM((int32_t) pid_update(&motor_l_speed_pid, (float) encoder1_speed));
    MOTOR_R_PWM((int32_t) pid_update(&motor_r_speed_pid, (float) encoder2_speed));
}
