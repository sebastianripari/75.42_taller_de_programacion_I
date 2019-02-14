/*
Enunciado:
Que es un functor? Ejemplifique.
*/

/*
Un functor es una claes, que se utiliza con el objetivo de ejecutar
una funcion con los parametros seteados en la construccion del objeto.
Es decir, se logra separar el pasaje de parametros de la ejecucion
de la funcion, cosa que con una funcion no es posible.
*/

#include <string>
#include <iostream>

class Saludador {
	std::string nombre;

public:
	Saludador(std::string nombre) : nombre(nombre) {}
	void run() {
		std::cout << "Hola " << nombre << std::endl;
	}
};

int main() {
	Saludador saludador("Sebastian");
	saludador.run();
	return 0;
}