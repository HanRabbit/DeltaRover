#ifndef IR_H
#define IR_H

#include "stm32h7xx_hal.h"
#include "gpio.h"

#define IR_L1 HAL_GPIO_ReadPin(IR_L1_GPIO_Port, IR_L1_Pin)
#define IR_L2 HAL_GPIO_ReadPin(IR_L2_GPIO_Port, IR_L2_Pin)
#define IR_L3 HAL_GPIO_ReadPin(IR_L3_GPIO_Port, IR_L3_Pin)
#define IR_M HAL_GPIO_ReadPin(IR_M_GPIO_Port, IR_M_Pin)
#define IR_R1 HAL_GPIO_ReadPin(IR_R1_GPIO_Port, IR_R1_Pin)
#define IR_R2 HAL_GPIO_ReadPin(IR_R2_GPIO_Port, IR_R2_Pin)
#define IR_R3 HAL_GPIO_ReadPin(IR_R3_GPIO_Port, IR_R3_Pin)

void ir_control(void);
void ir_update(void);

#endif //IR_H
