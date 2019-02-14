#ifndef __FUNCION_H__
#define __FUNCION_H__

/**** Funcion ****/

#include <string>

class Funcion {
	unsigned int id;
	std::string id_sala;
	std::string titulo_pelicula;
	std::string fecha;
	std::string hora_de_inicio;

public:
	// Setea el id de la funcion.
	void set_id(const unsigned int id);
	// Retorna el id de la funcion.
	const unsigned int get_id() const;
	// Setea el id de la sala.
	void set_id_sala(const std::string &id_sala);
	// Retorna el id de la sala.
	const std::string& get_id_sala() const;
	// Setea el titulo de la pelicula.
	void set_titulo_pelicula(const std::string &titulo_pelicula);
	// Retorna el titulo de la pelicula.
	const std::string& get_titulo_pelicula() const;
	// Setea la fecha de la funcion.
	void set_fecha(const std::string &fecha);
	// Retorna la fecha de la funcion.
	const std::string& get_fecha() const;
	// Setea la hora de inicio de la funcion.
	void set_hora_de_inicio(const std::string &hora_de_inicio);
	// Retorna la hora de inicio de la funcion.
	const std::string& get_hora_de_inicio() const;
};

#endif
