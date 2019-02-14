#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <queue>

template <class T>
class Queue {
	std::queue<T> elementos;

public:
	// Agrega un elemento.
	void push(T elemento) {
		this->elementos.push_front(elemento);
	};
	// Quito un elemento.
	T pop() {
		this->elementos.pop_back();
	}
};

#endif