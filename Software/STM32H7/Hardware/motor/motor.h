#ifndef MOTOR_H
#define MOTOR_H

#include "stm32h7xx_hal.h"
#include "gpio.h"
#include "tim.h"
#include "../../Utils/pid/pid.h"
#include <stdlib.h>
#include <stdbool.h>

extern __IO int32_t encoder1_speed;
extern __IO int32_t encoder2_speed;

#define MOTOR_L_SWITCH(speed) { HAL_GPIO_WritePin(Motor_L_A_GPIO_Port, Motor_L_A_Pin, speed > 0 ? GPIO_PIN_SET : GPIO_PIN_RESET); HAL_GPIO_WritePin(Motor_L_B_GPIO_Port, Motor_L_B_Pin, speed < 0 ? GPIO_PIN_SET : GPIO_PIN_RESET); }
#define MOTOR_R_SWITCH(speed) { HAL_GPIO_WritePin(Motor_R_A_GPIO_Port, Motor_R_A_Pin, speed > 0 ? GPIO_PIN_SET : GPIO_PIN_RESET); HAL_GPIO_WritePin(Motor_R_B_GPIO_Port, Motor_R_B_Pin, speed < 0 ? GPIO_PIN_SET : GPIO_PIN_RESET); }

#define MOTOR_ENABLE() HAL_GPIO_WritePin(Motor_EN_GPIO_Port, Motor_EN_Pin, GPIO_PIN_SET)
#define MOTOR_DISABLE() HAL_GPIO_WritePin(Motor_EN_GPIO_Port, Motor_EN_Pin, GPIO_PIN_RESET)

#define MOTOR_L_PWM(pulse) { MOTOR_L_SWITCH(pulse); __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, pulse > 0 ? pulse : -pulse); }
#define MOTOR_R_PWM(pulse) { MOTOR_R_SWITCH(pulse); __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pulse > 0 ? pulse : -pulse); }

#define MOTOR_UPDATE_FREQ 1.0f

void motor_l_set_speed(int32_t speed);
void motor_r_set_speed(int32_t speed);
void motor_update(void);
void motor_init(void);
void motor_set_speed(int32_t l_speed, int32_t r_speed);
void motor_set_position(int32_t l_pos, int32_t r_pos, int32_t speed);
void motor_position_reset(void);
void motor_set_forward(float m, int32_t speed);

extern PID_t motor_l_speed_pid;
extern PID_t motor_r_speed_pid;

extern PID_t motor_l_position_pid;
extern PID_t motor_r_position_pid;

extern __IO int32_t motor_l_position;
extern __IO int32_t motor_r_position;

extern bool motor_enable_position;

#endif //MOTOR_H
