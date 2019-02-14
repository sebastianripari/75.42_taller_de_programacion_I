#ifndef __PELICULA_H__
#define __PELICULA_H__

/**** Pelicula ****/ 

#include <string>

class Pelicula {
	std::string titulo;
	std::string idioma;
	std::string restriccion_de_edad;
	std::string genero;

public:
	// Setea el titulo de la pelicula.
	void set_titulo(const std::string &titulo);
	// Retorna el titulo de la pelicula.
	const std::string& get_titulo() const;
	// Setea el idioma de la pelicula.
	void set_idioma(const std::string &idioma);
	// Retorna el idioma de la pelicula.
	const std::string& get_idioma() const;
	// Setea la restriccion de edad de la pelicula.
	void set_restriccion_de_edad(const std::string &restriccion_de_edad);
	// Retorna la restriccion de edad de la pelicula.
	const std::string& get_restriccion_de_edad() const;
	// Setea el genero de la pelicula.
	void set_genero(const std::string & genero);
	// Retorna el genero de la pelicula.
	const std::string& get_genero() const;
};

#endif
