#ifndef IR_H
#define IR_H

#include "stm32h7xx_hal.h"
#include "gpio.h"

#define IR_O1 !HAL_GPIO_ReadPin(IR_O1_GPIO_Port, IR_O1_Pin)
#define IR_O2 !HAL_GPIO_ReadPin(IR_O2_GPIO_Port, IR_O2_Pin)
#define IR_O3 !HAL_GPIO_ReadPin(IR_O3_GPIO_Port, IR_O3_Pin)
#define IR_O4 !HAL_GPIO_ReadPin(IR_O4_GPIO_Port, IR_O4_Pin)

void ir_control(void);

#endif //IR_H
