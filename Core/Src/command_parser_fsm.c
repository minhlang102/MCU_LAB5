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
			if (buffer_list->tail->data == '!') {
				state_parser = S1;
				buffer_list->tail->state = state_parser;
			} else if (buffer_list->tail->data == '\b') {
				delete(buffer_list);
				delete(buffer_list);
			}
			if (buffer_list->size > 0 && buffer_list->tail->state != -1) {
				state_parser = buffer_list->tail->state;
			}
			break;
		case S1:
			if (buffer_list->tail->data == 'R') {
				state_parser = S2;
				buffer_list->tail->state = state_parser;
			} else if (buffer_list->tail->data == 'O') {
				state_parser = S6;
				buffer_list->tail->state = state_parser;
			} else if (buffer_list->tail->data == '!') {
				state_parser = S1;
				buffer_list->tail->state = state_parser;
			} else if (buffer_list->tail->data == '\b') {
				delete(buffer_list);
				delete(buffer_list);
				state_parser = INIT;
			} else {
				state_parser = INIT;
			}
			break;
		case S2:
			if (buffer_list->tail->data == 'S') {
				state_parser = S3;
				buffer_list->tail->state = state_parser;
			} else if (buffer_list->tail->data == '\b') {
				delete(buffer_list);
				delete(buffer_list);
				state_parser = S1;
			} else {
				state_parser = INIT;
			}
			break;
		case S3:
			if (buffer_list->tail->data == 'T') {
				state_parser = S4;
				buffer_list->tail->state = state_parser;
			} else if (buffer_list->tail->data == '\b') {
				delete(buffer_list);
				delete(buffer_list);
				state_parser = S2;
			} else {
				state_parser = INIT;
			}
			break;
		case S4:
			if (buffer_list->tail->data == '#') {
				state_parser = S5;
				buffer_list->tail->state = state_parser;
			} else if(buffer_list->tail->data == '\b') {
				delete(buffer_list);
				delete(buffer_list);
				state_parser = S3;
			} else {
				state_parser = INIT;
			}
			break;
		case S5:
			if (buffer_list->tail->data == '\r') {
				HAL_ADC_Start(&hadc1);
				ADC_value = ceil(HAL_ADC_GetValue(&hadc1));
				sprintf(data, "!ADC=%d#\r\n", ADC_value);
				command_flag = 1;
				sprintf(command_data, "%s", "!RST#");
				clear(buffer_list);
				state_parser = INIT;
			} else if (buffer_list->tail->data == '\b') {
				delete(buffer_list);
				delete(buffer_list);
				state_parser = S4;
			} else {
				state_parser = INIT;
			}
			break;
		case S6:
			if (buffer_list->tail->data == 'K') {
				state_parser = S7;
				buffer_list->tail->state = state_parser;
			} else if (buffer_list->tail->data == '\b') {
				delete(buffer_list);
				delete(buffer_list);
				state_parser = S1;
			} else {
				state_parser = INIT;
			}
			break;
		case S7:
			if (buffer_list->tail->data == '#') {
				state_parser = S8;
				buffer_list->tail->state = state_parser;
			} else if (buffer_list->tail->data == '\b') {
				delete(buffer_list);
				delete(buffer_list);
				state_parser = S6;
			} else {
				state_parser = INIT;
			}
			break;
		case S8:
			if (buffer_list->tail->data == '\r') {
				command_flag = 0;
				sprintf(command_data, "%s", "!OK#");
				clear(buffer_list);
				state_parser = INIT;
			} else if (buffer_list->tail->data == '\b') {
				delete(buffer_list);
				delete(buffer_list);
				state_parser = S7;
			} else {
				state_parser = INIT;
			}
			break;
		default:
			break;
	}
}

