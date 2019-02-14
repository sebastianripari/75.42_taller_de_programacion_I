#include <list>
#include <string>
#include "server_funciones.h"
#include "server_funcion.h"

std::list<Funcion> Funciones::listar_por_fecha(const std::string &fecha) const {
	std::list<Funcion> v;

	for (const Funcion& funcion : this->funciones) 
		if (funcion.get_fecha() == fecha) v.push_front(funcion);
			
	return std::move(v);
}

const Funcion& Funciones::get_funcion(const unsigned int id) const {
	for (const Funcion& funcion : this->funciones) 
		if (funcion.get_id() == id) return funcion;

	throw std::runtime_error(std::string("id funcion invalido"));
}

const std::string Funciones::get_id_sala(const unsigned int id_funcion) const {
	for (const Funcion& funcion : this->funciones) 
		if (funcion.get_id() == id_funcion) 
			return funcion.get_id_sala();

	throw std::runtime_error(std::string("id funcion invalido"));
}

void Funciones::add(Funcion funcion) {
	this->funciones.push_front(funcion);
}
