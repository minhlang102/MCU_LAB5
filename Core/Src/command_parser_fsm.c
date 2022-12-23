/*
 * command_parser_fsm.c
 *
 *  Created on: Dec 14, 2022
 *      Author: minhl
 */

#include "command_parser_fsm.h"

uint32_t ADC_value;
uint32_t invalid_char;


void command_parser_fsm(ADC_HandleTypeDef hadc1) {
	switch (state_parser) {
		case INIT:
			if (buffer[index_buffer-1] == '!') {
				invalid_char = 0;
				state_parser = S1;
			}
			break;
		case STUFF:
			if (buffer[index_buffer-1] == '\b') {
				invalid_char--;
				if (invalid_char == 0) {
					state_parser = last_state;
				}
			} else {
				invalid_char++;
			}
			break;
		case S1:
			if (buffer[index_buffer-1] == 'R') {
				state_parser = S2;
			} else if (buffer[index_buffer-1] == 'O') {
				state_parser = S6;
			} else if (buffer[index_buffer-1] == '!') {
				state_parser = S1;
			} else if (buffer[index_buffer-1] == '\b') {
				state_parser = INIT;
			} else {
				invalid_char++;
				last_state = S1;
				state_parser = STUFF;
			}
			break;
		case S2:
			if (buffer[index_buffer-1] == 'S') {
				state_parser = S3;
			} else if (buffer[index_buffer-1] == '\b') {
				state_parser = S1;
			} else {
				invalid_char++;
				last_state = S2;
				state_parser = STUFF;
			}
			break;
		case S3:
			if (buffer[index_buffer-1] == 'T') {
				state_parser = S4;
			} else if (buffer[index_buffer-1] == '\b') {
				state_parser = S2;
			} else {
				invalid_char++;
				last_state = S3;
				state_parser = STUFF;
			}
			break;
		case S4:
			if (buffer[index_buffer-1] == '#') {
				state_parser = S5;
			} else if(buffer[index_buffer-1] == '\b') {
				state_parser = S3;
			} else {
				invalid_char++;
				last_state = S4;
				state_parser = STUFF;
			}
			break;
		case S5:
			if (buffer[index_buffer-1] == '\r') {
				HAL_ADC_Start(&hadc1);
				ADC_value = ceil(HAL_ADC_GetValue(&hadc1));
				sprintf(data, "!ADC=%d#\r\n", ADC_value);
				command_flag = 1;
				sprintf(command_data, "%s", "!RST#");
				invalid_char = 0;
				state_parser = INIT;
			} else if (buffer[index_buffer-1] == '\b') {
				state_parser = S4;
			} else {
				invalid_char++;
				last_state = S5;
				state_parser = STUFF;
			}
			break;
		case S6:
			if (buffer[index_buffer-1] == 'K') {
				state_parser = S7;
			} else if (buffer[index_buffer-1] == '\b') {
				state_parser = S1;
			} else {
				invalid_char++;
				last_state = S6;
				state_parser = STUFF;
			}
			break;
		case S7:
			if (buffer[index_buffer-1] == '#') {
				state_parser = S8;
			} else if (buffer[index_buffer-1] == '\b') {
				state_parser = S6;
			} else {
				invalid_char++;
				last_state = S7;
				state_parser = STUFF;
			}
			break;
		case S8:
			if (buffer[index_buffer-1] == '\r') {
				command_flag = 0;
				sprintf(command_data, "%s", "!OK#");
				state_parser = INIT;
			} else if (buffer[index_buffer-1] == '\b') {
				state_parser = S7;
			} else {
				invalid_char++;
				last_state = S8;
				state_parser = STUFF;
			}
			break;
		default:
			break;
	}
}

