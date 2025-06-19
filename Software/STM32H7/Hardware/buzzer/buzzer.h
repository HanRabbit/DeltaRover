#ifndef BUZZER_H
#define BUZZER_H

#include "stm32h7xx_hal.h"
#include "gpio.h"

#define BUZZER_ON() HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2)
#define BUZZER_OFF() HAL_TIM_PWM_Stop(&htim12, TIM_CHANNEL_2)
#define BUZZER_TOGGLE(time) BUZZER_ON(); HAL_Delay(time); BUZZER_OFF();

#endif //BUZZER_H
