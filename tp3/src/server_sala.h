#ifndef __SALA_H__
#define __SALA_H__

/**** Sala ****/

#include <string>
#include "common_matrix.h"

class Sala {
	std::string id;
	std::string tipo_de_pantalla;
	std::string capacidad;
	Matrix asientos;

public:
	// Constructor;
	Sala();
	// Constructor por movimiento.
	Sala(Sala &&other);
	// Devuelve un string mostrando todos los asientos que posee la sala.
	// A los asientos libre los denota con el caracter 'O'
	// y a los reservados con 'X'.
	std::string ver_asientos() const;
	// Reserva un asiento en la posicion indicada en los parametros
	// Fila: 'fila'. Columna: 'c'.
	// Si pudo reservar retorna 'true', sino pudo porque
	// estaba reservado el asiento retorna false.
	bool reservar(const char fila, const unsigned int c);
	// Informa si la sala esta agotada. Es decir si 
	// tiene todos sus asientos reservados.
	// Retorna 'true' si esta agotada, 'false' sino.
	bool esta_agotada() const;
	// Setea el id de la sala.
	void set_id(const std::string &id);
	// Retorna el id de la sala.
	const std::string& get_id() const;
	// Setea el tipo de pantalla de la sala. Que puede ser '2D', '3D' o '4D'.
	void set_tipo_de_pantalla(const std::string &tipo_de_pantalla);
	// Setea la capacidad de la sala. Que puede ser 'chica', 'mediana' o 'grande'.
	void set_capacidad(const std::string &capacidad);
};

#endif
