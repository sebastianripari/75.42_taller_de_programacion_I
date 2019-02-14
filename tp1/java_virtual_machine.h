#ifndef __JAVA_VIRTUAL_MACHINE_H__
#define __JAVA_VIRTUAL_MACHINE_H__

/*** Java Virtual Machine ***/

#include "stack.h"

typedef struct { 
	stack_t* stack;
	int *numbers;
} jvm_t;

// Crea la virtual machine.
void jvm_create(jvm_t *self, int N);
// Ejecuta la instruccion bipush.
// Pre: self apunta un sector valido de memoria.
void jvm_execute_instruction_bipush(jvm_t *self, int data);
// Ejecuta la instruccion dup.
// Pre: self apunta un sector valido de memoria.
void jvm_execute_instruction_dup(jvm_t *self);
// Ejecuta la instruccion store.
// Pre: self apunta un sector valido de memoria.
void jvm_execute_instruction_istore(jvm_t *self, char c);
// Ejecuta la instruccion load.
// Pre: self apunta un sector valido de memoria.
void jvm_execute_instruction_iload(jvm_t *self, char c);
// Ejecuta la instruccion and.
// Pre: self apunta un sector valido de memoria.
void jvm_execute_instruction_iand(jvm_t *self);
// Ejecuta la instruccion or.
// Pre: self apunta un sector valido de memoria.
void jvm_execute_instruction_ior(jvm_t *self);
// Ejecuta la instruccion xor.
// Pre: self apunta un sector valido de memoria.
void jvm_execute_instruction_ixor(jvm_t *self);
// Ejecuta la instruccion rem.
// Pre: self apunta un sector valido de memoria.
void jvm_execute_instruction_irem(jvm_t *self);
// Ejecuta la instruccion neg.
// Pre: self apunta un sector valido de memoria.
void jvm_execute_instruction_ineg(jvm_t *self);
// Ejecuta la instruccion div.
// Pre: self apunta un sector valido de memoria.
void jvm_execute_instruction_idiv(jvm_t *self);
// Ejecuta la instruccion add.
// Pre: self apunta un sector valido de memoria.
void jvm_execute_instruction_iadd(jvm_t *self);
// Ejecuta la instruccion mul.
// Pre: self apunta un sector valido de memoria.
void jvm_execute_instruction_imul(jvm_t *self);
// Ejecuta la instruccion sub.
// Pre: self apunta un sector valido de memoria.
void jvm_execute_instruction_isub(jvm_t *self);
// Devuelve las variables.
// Pre: self apunta un sector valido de memoria.
int* jvm_get_variables_array(jvm_t *self);
// Libera los recursos asociados a la instacia self.
// Pre: self apunta un sector valido de memoria.
void jvm_destroy(jvm_t *self);

#endif
