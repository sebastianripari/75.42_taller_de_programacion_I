#ifndef __SALAS_H__
#define __SALAS_H__

/**** Salas ****/

#include <list>
#include <string>
#include <mutex>
#include "server_sala.h"

class Salas {
	std::list<Sala> salas;
	std::mutex m;

public:
	// Agrega la sala pasada como parametro.
	void add(Sala &&sala);
	// Reserva en la sala con id especificado en el parametro 'id',
	// en la fila 'f', columna 'c'.
	// Si pudo reservar retorna 'true', sino pudo 'false'.
	// El metodo es thread safe.
	bool reservar(const std::string &id, const char f, const unsigned int c);
	// Informa si la sala esta agotada, es decir que posee
	// todos los asientos reservados.
	// Retorna 'true' si esta agotada, 'false' sino.
	// El metodo es thread safe.
	bool esta_agotada(const std::string &id);
	// Informa si la sala con el 'id' pasado como parametro 
	// existe entre las cargadas.
	// Retorna 'true' si existe, 'false' sino.
	bool exist(const std::string &id);
	// Informa todos los asientos que posee la sala
	// A los asientos libre los denota con el caracter 'O' y
	// a los reservados con 'X'.
	// Esta informacion es seteada en el segundo parametro.
	// Informa si la sala esta agotada, es decir que posee
	// todos los asientos reservados. 
	// Esta informacion es seteada en el tercer parametro.
	// Si el id_sala es invalido se arroja una excepcion (std::runtime_error).
	// El metodo es thread safe.
	void ver_asientos(
		const std::string &id_sala,
		std::string &asientos,
		bool &esta_agotada);
};

#endif
