#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include "node.h"

void stack_create(stack_t *self) {
	self->head = NULL;
}

void stack_push(stack_t *self, int data) {
	node_t *node = malloc(sizeof(node_t));
	node_create(node);
	node_set_data(node, data);

	if(self->head != NULL) {
		node_set_next(node, self->head);
	}
	self->head = node;
}

int stack_pop(stack_t *self) {
	int data = node_get_data(self->head);
	node_t* to_delete = self->head;
	self->head = node_get_next(self->head);
	free(to_delete);
	return data;
}

int stack_top(stack_t *self) {
	return node_get_data(self->head);
}

void stack_destroy(stack_t *self) {
	if(self->head != NULL) {
		stack_pop(self);
		stack_destroy(self);
	}
}
