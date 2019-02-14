#include "java_virtual_machine.h"
#include <stdio.h>
#include <stdlib.h>

void jvm_create(jvm_t *self, int N) {
	self->stack = malloc(sizeof(stack_t));
	stack_create(self->stack);

	self->numbers = malloc(sizeof(int)*N);
	for (int i=0; i<N; ++i) self->numbers[i] = 0;
}

void jvm_execute_instruction_bipush(jvm_t *self, int number) {
	stack_push(self->stack, number);
}

void jvm_execute_instruction_dup(jvm_t *self) {
	stack_push(self->stack, stack_top(self->stack));
}

void jvm_execute_instruction_istore(jvm_t *self, char c) {
	char hex[3];
	hex[0] ='\0';
	snprintf(hex, sizeof(hex), "%02X", c);
	hex[2] ='\0';
	int pos = (int) strtol(hex, (char **)NULL, 10);
	self->numbers[pos] = stack_pop(self->stack);
} 

void jvm_execute_instruction_iload(jvm_t *self, char c) {
	char hex[3];
	hex[0] ='\0';
	snprintf(hex, sizeof(hex), "%02X", c);
	hex[2] ='\0';
	int pos = (int) strtol(hex, (char **)NULL, 10);
	stack_push(self->stack, self->numbers[pos]);
} 

void jvm_execute_instruction_iadd(jvm_t *self) {
	stack_push(self->stack, stack_pop(self->stack) + stack_pop(self->stack));
}

void jvm_execute_instruction_isub(jvm_t *self) {
	int a = stack_pop(self->stack);
	int b = stack_pop(self->stack);
	stack_push(self->stack, b - a);
}

void jvm_execute_instruction_imul(jvm_t *self) {
	stack_push(self->stack, stack_pop(self->stack) * stack_pop(self->stack));
}

void jvm_execute_instruction_idiv(jvm_t *self) {
	int a = stack_pop(self->stack);
	int b = stack_pop(self->stack);
	stack_push(self->stack, b / a);
}

void jvm_execute_instruction_irem(jvm_t *self) {
	int a = stack_pop(self->stack);
	int b = stack_pop(self->stack);
	stack_push(self->stack, b % a);
}

void jvm_execute_instruction_ineg(jvm_t *self) {
	stack_push(self->stack, -stack_pop(self->stack));
}

void jvm_execute_instruction_iand(jvm_t *self) {
	stack_push(self->stack, stack_pop(self->stack) & stack_pop(self->stack));
}

void jvm_execute_instruction_ior(jvm_t *self) {
	stack_push(self->stack, stack_pop(self->stack) | stack_pop(self->stack));
}

void jvm_execute_instruction_ixor(jvm_t *self) {
	stack_push(self->stack, stack_pop(self->stack) ^ stack_pop(self->stack));
}

int* jvm_get_variables_array(jvm_t *self) {
	return self->numbers;
}

void jvm_destroy(jvm_t *self) {
	stack_destroy(self->stack);
	free(self->stack);
	free(self->numbers);
}
