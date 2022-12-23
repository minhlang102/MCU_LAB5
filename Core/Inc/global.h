/*
 * global.h
 *
 *  Created on: Dec 14, 2022
 *      Author: minhl
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "stm32f1xx_hal_adc.h"
#include "stm32f1xx_hal_uart.h"

#define INIT				0
#define S1					1
#define S2					2
#define S3					3
#define S4					4
#define S5					5
#define S6					6
#define S7					7
#define S8					8
#define SEND				11
#define WAIT				12
#define STUFF				13
#define MAX_BUFFER_SIZE		30
#define MAX_DATA_SIZE 		5

extern uint8_t state_parser;
extern uint8_t state_uart;
extern uint8_t temp;
extern uint8_t buffer[MAX_BUFFER_SIZE];
extern uint8_t index_buffer;
extern uint8_t buffer_flag;
extern uint8_t command_flag;
extern uint8_t command_data[6];
extern uint8_t data[12];
extern uint8_t last_state;

#endif /* INC_GLOBAL_H_ */
