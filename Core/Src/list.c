/*
 * list.c
 *
 *  Created on: Dec 23, 2022
 *      Author: minhl
 */

#include "list.h"

void insert(struct list* p, uint8_t c) {
	if (p->size == 0) {
		struct node* tmp = (struct node*)malloc(sizeof(struct node));
		tmp->data = c;
		tmp->state = -1;
		tmp->next = NULL;
		tmp->prev = NULL;
		p->head = tmp;
		p->tail = tmp;
		p->size++;
	} else {
		struct node* tmp = (struct node*)malloc(sizeof(struct node));
		tmp->data = c;
		tmp->state = -1;
		tmp->next = NULL;
		tmp->prev = p->tail;
		p->tail->next = tmp;
		p->tail = tmp;
		p->size++;
	}
}

void delete(struct list* p) {
	if (p->size <= 0) {
		return;
	}
	if (p->size == 1) {
		p->head->data = "\0";
		free(p->head);
		p->head = NULL;
		p->tail = NULL;
		p->size--;
	} else {
		p->head->data = "\0";
		p->tail = p->tail->prev;
		p->tail->next->prev = NULL;
		free(p->tail->next);
		p->tail->next = NULL;
		p->size--;
	}
}

void clear(struct list* p) {
	if (p->size <= 0) {
		return;
	}
	while(p->size != 0) {
		delete(p);
	}
}
