#ifndef __CONTAINER_H__
#define __CONTAINER_H__

/*
Ejemplo de Template, 
Definiendo los metodos en el cpp.
*/

/*
No compila.
*/

#include <set>

template<class T> class Container {
	std::set<T> bag;

public:
	void add(T element);

	void remove(T element);
};

#endif
