/*
 * global.c
 *
 *  Created on: Dec 14, 2022
 *      Author: minhl
 */

#include "global.h"

uint8_t buffer[MAX_BUFFER_SIZE];
int8_t state_parser = 0;
int8_t state_uart = 0;
uint8_t temp = 0;
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;
uint8_t command_flag = 0;
uint8_t command_data[6];
uint8_t data[12];
uint8_t last_state = 0;
struct list* buffer_list = NULL;


