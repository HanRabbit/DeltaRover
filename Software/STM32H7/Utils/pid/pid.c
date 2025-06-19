#include "pid.h"

void pid_init(PID_t *pid, const float kp, const float ki, const float kd, const float dt) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->target_speed = 0.0f;
    pid->current_speed = 0.0f;
    pid->last_error = 0.0f;
    pid->integral = 0.0f;
    pid->output = 0.0f;
    pid->dt = dt;
    pid->last_output = 0.0f;
    pid->mode = PID_MODE_POSITION;  /* 默认使用位置控制模式 */
}

/**
 * @brief 设置 PID 控制器的模式
 * @param pid 指向 PID_t 结构体的指针
 * @param mode 要设置的 PID 模式
 */
void pid_set_mode(PID_t *pid, PID_Mode_t mode) {
    pid->mode = mode;
}

/**
 * @brief 更新 PID 控制器的输出
 * @param pid 指向 PID_t 结构体的指针
 * @param current_speed 当前速度
 * @return 返回计算后的输出值
 */
float pid_update(PID_t *pid, const float current_speed) {
    pid->error = pid->target_speed - current_speed;
    pid->integral += pid->error * pid->dt;
    const float derivative = (pid->error - pid->last_error) / pid->dt;
    pid->last_error = pid->error;
    pid->output = pid->kp * pid->error + pid->ki * pid->integral + pid->kd * derivative;

    if (pid->mode == PID_MODE_POSITION)
        pid->output += pid->last_output; /* 在位置控制模式下，输出值累加上一次的输出值 */

    pid->last_output = pid->output;

    if (pid->target_speed == 0.0f)
        pid->integral = 0.0f;

    return pid->output;
}