#include <string>
#include "server_funcion.h"

void Funcion::set_id(const unsigned int id) {
	this->id = id;
}

const unsigned int Funcion::get_id() const {
	return this->id;
}

void Funcion::set_id_sala(const std::string &id_sala) {
	this->id_sala = id_sala;
}

const std::string& Funcion::get_id_sala() const {
	return this->id_sala;
}

void Funcion::set_titulo_pelicula(const std::string &titulo_pelicula) {
	this->titulo_pelicula = titulo_pelicula;
}

const std::string& Funcion::get_titulo_pelicula() const {
	return this->titulo_pelicula;
}

void Funcion::set_fecha(const std::string &fecha) {
	this->fecha = fecha;
}

const std::string& Funcion::get_fecha() const {
	return this->fecha;
}

void Funcion::set_hora_de_inicio(const std::string &hora_de_inicio) {
	this->hora_de_inicio = hora_de_inicio;
}

const std::string& Funcion::get_hora_de_inicio() const {
	return this->hora_de_inicio;
}
