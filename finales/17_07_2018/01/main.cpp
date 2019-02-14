/*
Enunciado.
Explique que es cada uno de los siguientes items,
haciendo referencia a su inicializacion,
su comportamiento y el area de memoria donde residen:                                                                                                                               

 - Una variable global static.                                                                                                  
 - Una variable local static.                                                                                                   
 - Un atributo de clase static.
*/

/*
Las variables static tienen el lifetime del programa.

Variable local static: 
Lifetime del programa.
Scope de donde se encuentra alojada.
Vive en el datasegment.

Variable global static: 
Lifetime del programa.
Scope de todo el archivo.
Vive en el datasegment.

Atributo de clase static.
Lifetime del programa.
Si es un atributo privado: El Scope 
sera en los metodos de esa clase.
Si es un atributo publico: El Scope
sera en todos los lugares donde se
use la clase.
Vive en el datasegment.
*/

#include <iostream>

void f() {
	// i es una variable estatica local.
	static int i = 0;
	std::cout << "n: " << i << std::endl; 
	++i;
}

int main() {
	f(); // Salida: n: 0
	f(); // Salida: n: 1
	f(); // Salida: n: 2
	f(); // Salida: n: 3
	f(); // Salida: n: 4
	return 0;
}