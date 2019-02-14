#include <iomanip>
#include <string>
#include <iostream>

#include "server_requests_handler.h"
#include "common_socket.h"
#include "common_constants.h"

#define MAX_STANDBY_CONNS 10

void Requests_handler::listar_por_idioma() {
	std::string idioma = this->socket.recv_str();
	if ((idioma != "ESP") &&
		(idioma != "SUB")) {
		this->socket.send_str(std::string("Idioma no reconocido") + '\n' + '\0');
		return;
	}

	for (const Pelicula& pelicula : this->peliculas.listar_por_idioma(idioma))
		this->socket.send_str(pelicula.get_titulo() + '\n');
	this->socket.send_char('\0');
}

void Requests_handler::listar_por_edad() {
	std::string edad = this->socket.recv_str();
	if ((edad != "ATP") &&
		(edad != "+13") &&
		(edad != "+18")) {
		this->socket.send_str(std::string("Edad no reconocida") + '\n' + '\0');
		return;
	}

	for (const Pelicula& pelicula : this->peliculas.listar_por_edad(edad))
		this->socket.send_str(pelicula.get_titulo() + '\n');
	this->socket.send_char('\0');
}

void Requests_handler::listar_por_genero() {
	std::string genero = this->socket.recv_str();
	if ((genero != "Drama")     &&
		(genero != "Accion")    &&
		(genero != "Comedia")   &&
		(genero != "Animacion") &&
		(genero != "Terror")    &&
		(genero != "Suspenso")) {
		this->socket.send_str(std::string("Genero no reconocido") + '\n' + '\0');
		return;
	}

	for (const Pelicula& pelicula : this->peliculas.listar_por_genero(genero))
		this->socket.send_str(pelicula.get_titulo() + '\n');
	this->socket.send_char('\0');
}

void Requests_handler::listar_por_fecha() {
	unsigned int dia = this->socket.recv_unsigned_int();
	unsigned int mes = this->socket.recv_unsigned_int();
	unsigned int anio = this->socket.recv_unsigned_int();
	
	std::stringstream fecha;
	fecha << std::setw(2) << std::setfill('0') << dia << '/' 
		  << std::setw(2) << std::setfill('0') << mes << '/'
				                               << anio;
	for (const Funcion& funcion :
	    this->funciones.listar_por_fecha(fecha.str())) {
		std::stringstream ss;
		ss 	<< std::to_string(funcion.get_id()) << ':' << ' '
			<< "<Funcion para" << ' ' << '"'
			<< funcion.get_titulo_pelicula() << '"' << ' '
			<< "en la sala" << ' ' << funcion.get_id_sala()             
			<< ' ' << "con fecha" << ' ' << funcion.get_fecha() 
			<< ' ' << "-" << ' ' << funcion.get_hora_de_inicio()
			<< '>';
		if(this->salas.esta_agotada(funcion.get_id_sala())) ss << ' ' << "AGOTADA";
		this->socket.send_str(ss.str() + '\n');
	}
	this->socket.send_char('\0');
}

void Requests_handler::ver_asientos() {
	unsigned int id_funcion = this->socket.recv_unsigned_int();
	std::string id_sala = this->funciones.get_id_sala(id_funcion);
	const Funcion &funcion = this->funciones.get_funcion(id_funcion);
	std::stringstream ss;
	ss 	<< std::to_string(funcion.get_id()) << ':' << ' '
		<< "<Funcion para" << ' ' << '"'
		<< funcion.get_titulo_pelicula() << '"' << ' '
		<< "en la sala" << ' ' << funcion.get_id_sala()             
		<< ' ' << "con fecha" << ' ' << funcion.get_fecha() 
		<< ' ' << "-" << ' ' << funcion.get_hora_de_inicio()
		<< '>';
	bool esta_agotada = false;
	std::string asientos;
	this->salas.ver_asientos(id_sala, asientos, esta_agotada);
	if(esta_agotada) ss << ' ' << "AGOTADA";
	this->socket.send_str(ss.str() + '\n');
	this->socket.send_str(std::string("Asientos:") + '\n');
	this->socket.send_str(asientos);
	this->socket.send_char('\0');
}

void Requests_handler::reservar() {
	unsigned int id_funcion = this->socket.recv_unsigned_int();
	char fila = this->socket.recv_char();
	unsigned int columna = this->socket.recv_unsigned_int();
	std::string id_sala = this->funciones.get_id_sala(id_funcion);
	bool response = this->salas.reservar(id_sala, fila, columna);
	if(response == true)
		this->socket.send_str(std::string("OK") + '\n');
	else 
		this->socket.send_str(std::string(
			"ERROR: El asiento ya está reservado") + '\n');
	this->socket.send_char('\0');
}

void Requests_handler::run() {
	unsigned int action;
	try {
		while(true) {
			action = this->socket.recv_unsigned_int();
			switch (action) {
				case LISTAR_POR_IDIOMA: this->listar_por_idioma();  break;
				case LISTAR_POR_EDAD:   this->listar_por_edad();    break;			 
				case LISTAR_POR_GENERO: this->listar_por_genero();  break;
				case LISTAR_POR_FECHA:  this->listar_por_fecha();   break;
				case VER_ASIENTOS: 		this->ver_asientos();       break;
				case RESERVAR:          this->reservar();           break;
			}
		}
	}
	catch (...) {
		// Cuando el socket cliente deja de enviar peticiones y 
		// procede a cerrase. Nosotros lo vemos desde aqui cuando hacemos
		// el recv de la 'action'. Si el socket client se cerro, entonces
		// socket.recv_unsigned_int() arrojara
		// una excepcion (std::runtime_error("socket desconectado")) 
		// diciendo que el cliente esta desconectado. La capturamos aqui,
		// para que deje de iterar en el bucle. Y este thread deje de
		// trabajar, solamente seteamos el flag que indica que esta muerto.
		// Para que eventualmente el recolector de basura de threads lo libere.
		this->is_dead = true;
	}
}
   
void Requests_handler::operator()() {
	this->run();  
}

bool Requests_handler::get_is_dead() {
	return this->is_dead;
}
