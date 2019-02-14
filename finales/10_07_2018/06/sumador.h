#ifndef __SUMADOR_H__
#define __SUMADOR_H__

#include <vector>

// La restriccion que debe existir es que 
// el tipo de dato T tenga implementado el 
// operador +.

template <class T>
class Sumador {
	std::vector<T> v;
public:
	Sumador(std::vector<T> v) : v(v) {}

	T sumar() {
		T suma = v.front();
		v.erase(v.begin());
		for(auto& it : this->v) suma  = suma + it;
		return suma;
	}
};

#endif
