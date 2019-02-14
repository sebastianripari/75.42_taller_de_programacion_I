#include "node.h"
#include <stdio.h>

void node_create(node_t* self) {
	self->data = 0;
	self->next = NULL;
}

void node_set_data(node_t* self, int data) {
	self->data = data;
}

int node_get_data(node_t* self) {
	return self->data;
}

void node_set_next(node_t* self, node_t* next) {
	self->next = next;
}

node_t* node_get_next(node_t* self) {
	return self->next;
}

void node_destroy(node_t* self) {
}
