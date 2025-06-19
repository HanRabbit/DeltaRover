#ifndef UART_CMD_H
#define UART_CMD_H

#include "main.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "usart.h"
#include "../../Hardware/motor/motor.h"
#include "../../Hardware/sys_info/sys_info.h"

#define UART_RX_BUFFER_SIZE 128
char uart_rx_buffer[UART_RX_BUFFER_SIZE];
uint8_t uart_rx_index = 0;

void process_cmd(uint8_t *rx_buffer);

#endif //UART_CMD_H
