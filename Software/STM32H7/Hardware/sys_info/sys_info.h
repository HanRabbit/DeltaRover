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

/* 串口状态打印 */
#define UART_STATUS_PRINT 0

/* 串口 PID 调参 */
#define UART_DEBUG 1

/* OLED 状态打印 */
#define OLED_STATUS_PRINT 1

void sys_init(void);
void sys_info_update(void);

#endif //SYS_INFO_H
