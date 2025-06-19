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
}

float pid_update(PID_t *pid, const float current_speed) {
    pid->error = pid->target_speed - current_speed;
    pid->integral += pid->error * pid->dt;
    if (pid->integral_max != pid->integral_min)
        pid->integral = fmaxf(pid->integral_min, fminf(pid->integral, pid->integral_max)); // 限制积分值在最大最小范围内
    const float derivative = (pid->error - pid->last_error) / pid->dt;
    pid->last_error = pid->error;
    pid->output = pid->last_output + pid->kp * pid->error + pid->ki * pid->integral + pid->kd * derivative;
    pid->last_output = pid->output;

    if (pid->target_speed == 0.0f) {
        pid->integral = 0.0f; // 如果目标速度为 0，清除积分项
    }

    return pid->output;
}