#ifndef __NODE_H__
#define __NODE_H__

/*** Nodo ***/

typedef struct node_t{ 
	int data;
	struct node_t* next;
} node_t;

// Crea el nodo.
// Pre: self apunta un sector valido de memoria
void node_create(node_t* self);
// Setea el dato "data" en el nodo.
// Pre: self apunta un sector valido de memoria
void node_set_data(node_t* self, int data);
// Devuelve el dato que guarda el nodo.
// Pre: self apunta un sector valido de memoria
int node_get_data(node_t* self);
// Setea la direccion del nodo al que apunta la instancia de nodo self.
// Pre: self apunta un sector valido de memoria
void node_set_next(node_t* self, node_t* next);
// Devuelve el nodo apuntado por la instacia "self".
// Pre: self apunta un sector valido de memoria
node_t* node_get_next(node_t* self);
// Destruye los recursos asosciados a la instacia de nodo self.
// Pre: self apunta un sector valido de memoria
void node_destroy(node_t* self);

#endif
