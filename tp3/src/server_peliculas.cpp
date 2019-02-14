#include <list>
#include <string>
#include "server_peliculas.h"
#include "server_pelicula.h"

std::list<Pelicula>
Peliculas::listar_por_idioma(const std::string &idioma) const {
	std::list<Pelicula> v;

	for (const Pelicula& pelicula : this->peliculas)
		if (pelicula.get_idioma() == idioma) v.push_front(pelicula);
		
	return std::move(v);
}

std::list<Pelicula>
Peliculas::listar_por_edad(const std::string &edad) const {
	std::list<Pelicula> v;

	for (const Pelicula& pelicula : this->peliculas)
		if (pelicula.get_restriccion_de_edad() == edad) v.push_front(pelicula);
		
	return std::move(v);
}

std::list<Pelicula>
Peliculas::listar_por_genero(const std::string &genero) const {
	std::list<Pelicula> v;

	for (const Pelicula& pelicula : this->peliculas)
		if (pelicula.get_genero() == genero) v.push_front(pelicula);
		
	return std::move(v);
}

void Peliculas::add(Pelicula pelicula) {
	this->peliculas.push_front(pelicula);
}

bool Peliculas::exist(const std::string &titulo) {
	for (const Pelicula& pelicula : this->peliculas)
		if (pelicula.get_titulo() == titulo) return true;
	return false;
}
