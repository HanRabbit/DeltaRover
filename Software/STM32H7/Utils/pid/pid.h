#ifndef PID_H
#define PID_H

#include "stm32h7xx_hal.h"

typedef enum {
    PID_MODE_POSITION,  /* 位置控制模式 */
    PID_MODE_SPEED      /* 速度控制模式 */
} PID_Mode_t;

typedef struct {
    float kp, ki, kd;
    float target;     /* 目标速度 */
    float current;    /* 当前速度 */
    float error;            /* 当前误差 */
    float last_error;       /* 上一次误差 */
    float integral;         /* 积分值 */
    float output;           /* 输出值 */
    float dt;               /* 时间间隔 */
    float last_output;      /* 上一次输出值 */
    float integral_max;     /* 积分最大值 */
    float integral_min;     /* 积分最小值 */
    PID_Mode_t mode;        /* PID 模式 */
} PID_t;

void pid_init(PID_t *pid, float kp, float ki, float kd, float dt);
void pid_set_mode(PID_t *pid, const PID_Mode_t mode);
float pid_update(PID_t *pid, float current_speed);

#endif //PID_H
