#ifndef SYS_INFO_H
#define SYS_INFO_H

#include "stm32h7xx_hal.h"
#include "tim.h"
#include "gpio.h"
#include "usart.h"
#include "string.h"
#include "stdio.h"
#include "../../Hardware/oled/oled.h"
#include "../../Hardware/buzzer/buzzer.h"
#include "../../Hardware/motor/motor.h"
#include "../../Hardware/ir/ir.h"

void sys_init(void);
void sys_info_update(void);

#endif //SYS_INFO_H
