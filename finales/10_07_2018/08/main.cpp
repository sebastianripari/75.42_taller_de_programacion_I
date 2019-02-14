/*
Enunciado.
Defina el concepto de Mutex y de un ejemplo de uso.
Indique en que casos es necesario.
*/

/*
Mutex = Mutual Exclusion.
Es un recurso para que podamos exijir que dos hilos 
de ejecucion no toquen el mismo recurso al mismo tiempo.
*/

#include "set_protected.h"
#include <iostream>
#include <thread>

void f(Set_protected* s) {
	for(int i = 0; i < 500; ++i) s->insert(i);
}

int main() {
	// Si comentamos los lock/unlock en la clase
	// Set_protected se observa como ocurre una sig fault
	// y termina el programa producto de no proteger el 
	// recurso ante el acceso de dos hilos al mismo tiempo.
	while(true) {
		Set_protected s;
		std::thread t(&f, &s);
		for(int i = 0; i < 500; ++i) s.erase(i);
		std::cout << s.size() << std::endl;
		t.join();
	}
	return 0;
}