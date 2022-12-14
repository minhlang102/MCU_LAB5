/*
 * uart_communication_fsm.c
 *
 *  Created on: Dec 14, 2022
 *      Author: minhl
 */

#include "uart_communication_fsm.h"

void uart_communication_fsm(UART_HandleTypeDef huart2) {
	switch (state_uart) {
		case INIT:
			if (command_flag == 1) {
				state_uart = SEND;
			}
			break;
		case SEND:
			HAL_UART_Transmit(&huart2, (void *) command_data, 12, 1000);
			setTimer2(3000);
			state_uart = WAIT;
			break;
		case WAIT:
			if (timer2_flag == 1) {
				state_uart = SEND;
			}
			if (command_flag == 0) {
				state_uart = INIT;
			}
			break;
		default:
			break;
	}
}
