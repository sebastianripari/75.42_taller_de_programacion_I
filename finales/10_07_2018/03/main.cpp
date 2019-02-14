/*
Enunciado.
Explique que es y para que sirve una variable de clase
(o atributo estatico) en C++. Mediante un ejemplo de uso,
indique como se define dicha variable, su inicializacion
y el acceso a su valor para realizar una impresion simple
dentro de un main.
*/

/*
Una variable de clase es un atributo de la clase que
es compartido por todas las instancias de esa clase.
*/

#include "documento.h"
#include <iostream>

long int Documento::n = 0;

int main() {
	Documento dni_1("Sebastian", "Ripari", 'M');
	Documento dni_2("Thomas", "Ripari", 'M');
	
	std::cout << dni_1.obtener_numero() << std::endl;
	std::cout << dni_2.obtener_numero() << std::endl;
	std::cout << "Cantidad de Personas: " << Documento::n << std::endl;
	return 0;
}