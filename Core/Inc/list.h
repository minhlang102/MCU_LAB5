/*
 * list.h
 *
 *  Created on: Dec 23, 2022
 *      Author: minhl
 */

#ifndef INC_LIST_H_
#define INC_LIST_H_

#include "main.h"
#include "stdlib.h"

struct node {
	uint8_t data;
	int8_t state;
	struct node* next;
	struct node* prev;
};

struct list {
	struct node* head;
	struct node* tail;
	uint32_t size;
};

void insert(struct list* p, uint8_t c);
void delete(struct list* p);
void clear(struct list* p);

#endif /* INC_LIST_H_ */
