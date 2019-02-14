#include <string>
#include <sstream>
#include "server_sala.h"

Sala::Sala() {
}

Sala::Sala(Sala &&other) {
	this->id = other.id;
	this->tipo_de_pantalla = other.tipo_de_pantalla;
	this->capacidad = other.capacidad;
	this->asientos = std::move(other.asientos);
}

std::string Sala::ver_asientos() const {
	std::stringstream ss;

	for(unsigned int i=1; i <= this->asientos.get_cantidad_de_columnas(); ++i)
		ss << '\t' << i;
	ss << std::endl;

	for(unsigned int i=0; i < this->asientos.get_cantidad_de_filas(); ++i) {
		switch (i) {
			case  0: ss << 'A'; break; case  8: ss << 'I'; break;
			case  1: ss << 'B'; break; case  9: ss << 'J'; break;
			case  2: ss << 'C'; break; case 10: ss << 'K'; break;
			case  3: ss << 'D'; break; case 11: ss << 'L'; break;
			case  4: ss << 'E'; break; case 12: ss << 'M'; break;
			case  5: ss << 'F'; break; case 13: ss << 'N'; break;
			case  6: ss << 'G'; break; case 14: ss << 'O'; break;
			case  7: ss << 'H'; break;
		}
			
		for(unsigned int j=0; j < this->asientos.get_cantidad_de_columnas(); ++j) 
			ss << '\t' << this->asientos.get(i,j);
		ss << std::endl;
	}

	return ss.str();
}

bool Sala::reservar(const char fila, const unsigned int c) {
	unsigned int f = 0;

	switch (fila) {
		case 'A': f =  0; break; case 'I': f =  8; break;
		case 'B': f =  1; break; case 'J': f =  9; break;
		case 'C': f =  2; break; case 'K': f = 10; break;
		case 'D': f =  3; break; case 'L': f = 11; break;
		case 'E': f =  4; break; case 'M': f = 12; break;
		case 'F': f =  5; break; case 'N': f = 13; break;
		case 'G': f =  6; break; case 'O': f = 14; break;
		case 'H': f =  7; break;
	}

	return this->asientos.set(f, c);
}

bool Sala::esta_agotada() const {
	return asientos.full();
}

void Sala::set_id(const std::string &id) {
	this->id = id;
}

const std::string& Sala::get_id() const {
	return this->id;
}

void Sala::set_tipo_de_pantalla(const std::string &tipo_de_pantalla) {
	this->tipo_de_pantalla = tipo_de_pantalla;
}

void Sala::set_capacidad(const std::string &capacidad) {
	this->capacidad = capacidad;
	if (capacidad == std::string("chica")) 
		this->asientos = std::move(Matrix(05, 06));
	else if (capacidad == std::string("mediana")) 
		this->asientos = std::move(Matrix(10, 11));
	else if (capacidad == std::string("grande")) 
		this->asientos = std::move(Matrix(15, 16));
}
