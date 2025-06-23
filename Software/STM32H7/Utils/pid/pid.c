#include "pid.h"

#include <stdlib.h>

void pid_init(PID_t *pid, const float kp, const float ki, const float kd, const float dt) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->target = 0.0f;
    pid->current = 0.0f;
    pid->last_error = 0.0f;
    pid->integral = 0.0f;
    pid->output = 0.0f;
    pid->dt = dt;
    pid->last_output = 0.0f;
    pid->mode = PID_MODE_POSITION;  /* 默认使用位置控制模式 */
    pid->integral_max = 0.0f;       /* 积分最大值 */
    pid->integral_min = 0.0f;      /* 积分最小值 */
}

/**
 * @brief 设置 PID 控制器的模式
 * @param pid 指向 PID_t 结构体的指针
 * @param mode 要设置的 PID 模式
 */
void pid_set_mode(PID_t *pid, const PID_Mode_t mode) {
    pid->mode = mode;
}

/**
 * @brief 设置 PID 控制器的输出限幅
 * @param pid 指向 PID_t 结构体的指针
 * @param output_min 输出最小值
 * @param output_max 输出最大值
 */
void pid_set_output_limits(PID_t *pid, const float output_min, const float output_max) {
    pid->output_min = output_min;
    pid->output_max = output_max;
}

/**
 * @brief 设置 PID 控制器的积分限幅
 * @param pid 指向 PID_t 结构体的指针
 * @param integral_min 积分最小值
 * @param integral_max 积分最大值
 */
void pid_set_integral_limits(PID_t *pid, const float integral_min, const float integral_max) {
    pid->integral_min = integral_min;
    pid->integral_max = integral_max;
}

/**
 * @brief 更新 PID 控制器的输出
 * @param pid 指向 PID_t 结构体的指针
 * @param current_speed 当前速度
 * @return 返回计算后的输出值
 */
float pid_update(PID_t *pid, const float current_speed) {
    pid->error = pid->target - current_speed;
    pid->integral += pid->error * pid->dt;
    /* 积分限幅 */
    if (pid->integral_min != pid->integral_max) {
        if (pid->integral > pid->integral_max) {
            pid->integral = pid->integral_max;
        } else if (pid->integral < pid->integral_min) {
            pid->integral = pid->integral_min;
        }
    }
    const float derivative = (pid->error - pid->last_error) / pid->dt;
    pid->last_error = pid->error;
    pid->output = pid->kp * pid->error + pid->ki * pid->integral + pid->kd * derivative;

    if (pid->mode == PID_MODE_SPEED)
        pid->output += pid->last_output; /* 在位置控制模式下，输出值累加上一次的输出值 */

    /* 输出限幅 */
    if (pid->output_max != pid->output_min) {
        if (pid->output > pid->output_max) {
            pid->output = pid->output_max;
        } else if (pid->output < pid->output_min) {
            pid->output = pid->output_min;
        }
    }

    // if (fabsf(pid->output) < MOTOR_DIE_AREA && pid->output != 0.0f) {
    //     pid->output = MOTOR_DIE_AREA * (pid->output > 0 ? 1.0f : -1.0f); // 如果输出小于死区范围，则设置为死区范围
    // }
    if (fabsf(pid->output) < 10 && pid->mode == PID_MODE_SPEED)
        pid->output = 0.0f;

    pid->last_output = pid->output;

    if (pid->target == 0.0f)
        pid->integral = 0.0f;

    return pid->output;
}