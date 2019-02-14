#ifndef __DEQUE_H__
#define __DEQUE_H__

/**** Cola de enteros doblemente enlazada ****/

#include <deque>
#include <map>

class Deque {
	std::deque<int> q;
	std::map<int, bool> table;

/** Todos los metodos son "Thread safe" **/
public:
	// Busca si existe el entero i en la cola.
	// Lo hace de forma eficiente ya que indexa el elemento i,
	// en la tabla "table".
	// Post: Retorna true si el elemento se encuentra en la cola.
	//       Retorna false si el elemento no se encuentra en la cola.       
	bool find(const int i);
	// Informa el tamanio de la cola.
	unsigned int size();
	// Elimina el ultimo elemento de la cola.
	void pop_back();
	// Agrega un elemento a la cola.
	void push_front(const int i);
	// Elimina el elemento pasado como parametro en la cola.
	void erase(const int i);
};

#endif
