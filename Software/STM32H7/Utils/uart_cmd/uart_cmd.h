#ifndef UART_CMD_H
#define UART_CMD_H

#include "main.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "usart.h"
#include "../../Hardware/motor/motor.h"
#include "../../Hardware/sys_info/sys_info.h"

#define UART_RX_BUFFER_SIZE 14
extern char rx_byte;
extern int8_t rx_index;

void process_cmd(uint8_t *rx_buffer);

#endif //UART_CMD_H
