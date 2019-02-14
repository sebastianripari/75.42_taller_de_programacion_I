#ifndef __PELICULAS_H__
#define __PELICULAS_H__

/**** Peliculas ****/

#include <list>
#include <string>
#include "server_pelicula.h"

class Peliculas {
	std::list<Pelicula> peliculas;

public:
	// Lista las peliculas cargadas que poseen el idioma especificado
	// en el parametro.
	// Retorna una lista con las peliculas que poseen el idioma especificado.
	std::list<Pelicula> listar_por_idioma(const std::string &idioma) const;
	// Lista las peliculas cargadas que poseen la restriccion de edad especificada
	// en el parametro.
	// Retorna una lista con las peliculas que poseen dicha restriccion de edad.
	std::list<Pelicula> listar_por_edad(const std::string &edad) const;
	// Lista las peliculas cargadas que poseen el genero especificado
	// en el parametro.
	// Retorna una lista con las peliculas que poseen el genero especificado.
	std::list<Pelicula> listar_por_genero(const std::string &genero) const;
	// Agrega la pelicula pasada como parametro.
	void add(Pelicula pelicula);
	// Informa si la pelicula con el 'titulo' pasado como parametro
	// existe entre las cargadas.
	// Retorna 'true' si existe, 'false' sino.
	bool exist(const std::string &titulo);
};

#endif
