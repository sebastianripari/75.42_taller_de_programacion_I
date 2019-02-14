#include <string>
#include "server_pelicula.h"

void Pelicula::set_titulo(const std::string &titulo) {
	this->titulo = titulo;
}

const std::string& Pelicula::get_titulo() const {
	return this->titulo;
}

void Pelicula::set_idioma(const std::string &idioma) {
	this->idioma = idioma;
}

const std::string& Pelicula::get_idioma() const {
	return this->idioma;
}

void Pelicula::set_restriccion_de_edad(const std::string &restriccion_de_edad) {
	this->restriccion_de_edad = restriccion_de_edad;
}

const std::string& Pelicula::get_restriccion_de_edad() const {
	return this->restriccion_de_edad;
}

void Pelicula::set_genero(const std::string & genero) {
	this->genero = genero;
}

const std::string& Pelicula::get_genero() const {
	return this->genero;
}
