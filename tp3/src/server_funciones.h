#ifndef __FUNCIONES_H__
#define __FUNCIONES_H__

/**** Funciones ****/ 

#include <list>
#include <sstream>
#include <string>
#include "server_funcion.h"

class Funciones {
	std::list<Funcion> funciones;

public:
	// Lista las funciones cargadas que poseen la fecha
	// especificada en el parametro.
	// Retorna una lista con las funciones que poseen la fecha especificada.
	std::list<Funcion> listar_por_fecha(const std::string &fecha) const;
	// Retorna la funcion con el id especificado como parametro.
	// Si el id es invalido se arroja una excepcion (std::runtime_error).
	const Funcion& get_funcion(const unsigned int id) const;
	// Retorna el id de la sala de la funcion que posee
	// el id pasado como parametro.
	// Si el id funcion es invalido se arroja una excepcion (std::runtime_error).
	const std::string get_id_sala(const unsigned int id_funcion) const;
	// Agrega la funcion pasada como parametro.
	void add(Funcion funcion);
};

#endif
