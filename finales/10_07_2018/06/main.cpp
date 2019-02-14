#include "sumador.h"
#include <iostream>

int main() {
	// Ejemplo de uso 1.
	std::vector<int> v_1;
	v_1.push_back(2);
	v_1.push_back(3);
	Sumador<int> sumador_1(v_1);
	std::cout << sumador_1.sumar() << std::endl;

	// Ejemplo de uso 2.
	std::vector<std::string> v_2;
	v_2.push_back("sebas");
	v_2.push_back("tian");
	Sumador<std::string> sumador_2(v_2);
	std::cout << sumador_2.sumar() << std::endl;

	return 0;
}