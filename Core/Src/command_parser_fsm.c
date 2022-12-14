/*
 * command_parser_fsm.c
 *
 *  Created on: Dec 14, 2022
 *      Author: minhl
 */

#include "command_parser_fsm.h"

uint32_t ADC_value;

void command_parser_fsm(ADC_HandleTypeDef hadc1) {
	switch (state_parser) {
		case INIT:
			if (buffer[index_buffer-1] == '!') {
				state_parser = S1;
			}
			break;
		case S1:
			if (buffer[index_buffer-1] == 'R') {
				state_parser = S2;
			} else if (buffer[index_buffer-1] == 'O') {
				state_parser = S6;
			} else if (buffer[index_buffer-1] == '!') {
				state_parser = S1;
			} else {
				state_parser = INIT;
			}
			break;
		case S2:
			if (buffer[index_buffer-1] == 'S') {
				state_parser = S3;
			} else {
				state_parser = INIT;
			}
			break;
		case S3:
			if (buffer[index_buffer-1] == 'T') {
				state_parser = S4;
			} else {
				state_parser = INIT;
			}
			break;
		case S4:
			if (buffer[index_buffer-1] == '#') {
				state_parser = S5;
			} else {
				state_parser = INIT;
			}
			break;
		case S5:
			HAL_ADC_Start(&hadc1);
			ADC_value = ceil(HAL_ADC_GetValue(&hadc1));
			sprintf(command_data, "!ADC=%d#\r\n", ADC_value);
			command_flag = 1;
			state_parser = INIT;
			break;
		case S6:
			if (buffer[index_buffer-1] == 'K') {
				state_parser = S7;
			} else {
				state_parser = INIT;
			}
			break;
		case S7:
			if (buffer[index_buffer-1] == '#') {
				state_parser = S8;
			} else {
				state_parser = INIT;
			}
			break;
		case S8:
			command_flag = 0;
			state_parser = INIT;
			break;
		default:
			break;
	}
}

