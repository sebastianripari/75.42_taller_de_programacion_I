#ifndef __DOCUMENTO_H__
#define __DOCUMENTO_H__

#include <string>

class Documento {
	long int numero;
	std::string nombre;
	std::string apellido;
	char sexo;

public:
	static long int n;
	
	Documento(
		std::string nombre,
		std::string apellido,
		char sexo
	) :	numero(++n),
		nombre(nombre),
    	apellido(apellido),
		sexo(sexo) {};

	long int obtener_numero() {
		return this->numero;
	}
};

#endif