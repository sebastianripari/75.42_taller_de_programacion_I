#ifndef __CONTENEDOR_H__
#define __CONTENEDOR_H__

/*
Ejemplo de Template, 
Definiendo los metodos en el header.
*/

/*
Compila ok.
*/

#include <set>

template<class T> class Contenedor {
	std::set<T> bag;

public:
	void add(T element);

	void remove(T element);
};

template<class T> void Contenedor<T>::add(T element) {
	this->bag.insert(element);
}

template<class T> void Contenedor<T>::remove(T element) {
	this->bag.erase(element);
}

#endif
