#ifndef __STACK_H__
#define __STACK_H__

/*** Stack ***/

#include "node.h"

typedef struct { 
	node_t* head;
} stack_t;

// Crea un stack. 
// Pre: self apunta a un sector valido de memoria.
void stack_create(stack_t *self);
// Agrega el elemento pasado por parametro en el stack.
// Pre: self apunta un sector valido de memoria. 
void stack_push(stack_t *self, int data);
// Devuelve el elemento que esta en le tope de la pila pero sin sacarlo.
// Pre: self apunta un sector valido de memoria. 
int stack_top(stack_t *self);
// Devuelve el elemento que esta en le tope de la pila y lo saca.
// Pre: self apunta un sector valido de memoria. 
int stack_pop(stack_t *self);
// Destruye la instancia self liberando sus recursos. 
// Pre: self apunta un sector valido de memoria
//      self fue inicializado mediante stack_create
void stack_destroy(stack_t *self);

#endif
