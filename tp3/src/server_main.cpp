#include <sstream>
#include <iostream>
#include <string>
#include <vector>

#include "common_input.h"
#include "common_socket.h"
#include "common_thread.h"

#include "server_acceptor.h"
#include "server_sala.h"
#include "server_pelicula.h"
#include "server_funcion.h"

#include "server_peliculas.h"
#include "server_funciones.h"
#include "server_salas.h"

#define MAX_STANDBY_CONNS 10

void parse_salas_file(Salas &salas, const char *path) {
	Input salas_file;

	salas_file.open_file(path);

	if(!salas_file.is_open()) {
		std::stringstream ss;
		ss << "El archivo " << path << " no existe";
		throw std::invalid_argument(ss.str());
	}

	std::string sala_str;

	while(salas_file.get_line(sala_str)) {
		Sala sala;

		std::string id;
		std::string tipo_de_pantalla;
		std::string capacidad;

		std::istringstream s(sala_str);

		std::getline(s, id, ',');
		std::getline(s, tipo_de_pantalla, ',');
		std::getline(s, capacidad, ',');

		sala.set_id(id);
		sala.set_tipo_de_pantalla(tipo_de_pantalla);
		sala.set_capacidad(capacidad);

		salas.add(std::move(sala));
	}
}

void parse_peliculas_file(Peliculas &peliculas, const char *path) {
	Input peliculas_file;

	peliculas_file.open_file(path);

	if(!peliculas_file.is_open()) {
		std::stringstream ss;
		ss << "El archivo " << path << " no existe";
		throw std::invalid_argument(ss.str());
	}

	std::string pelicula_str;

	while(peliculas_file.get_line(pelicula_str)) {
		Pelicula pelicula;

		std::string titulo;
		std::string idioma;
		std::string restriccion_de_edad;
		std::string genero;

		std::istringstream p(pelicula_str);

		std::getline(p, titulo, ',');
		std::getline(p, idioma, ',');
		std::getline(p, restriccion_de_edad, ',');
		std::getline(p, genero, ',');

		pelicula.set_titulo(titulo);
		pelicula.set_idioma(idioma);
		pelicula.set_restriccion_de_edad(restriccion_de_edad);
		pelicula.set_genero(genero);

		peliculas.add(pelicula);
	}
}

void parse_funciones_file(
	Funciones &funciones,
	Peliculas &peliculas,
	Salas &salas,
	const char *path
) {
	Input funciones_file;

	funciones_file.open_file(path);

	if(!funciones_file.is_open()) {
		std::stringstream ss;
		ss << "El archivo " << path << " no existe";
		throw std::invalid_argument(ss.str());
	}

	std::string funcion_str;

	int id = 1;

	while(funciones_file.get_line(funcion_str)) {
		Funcion funcion;

		std::string id_sala;
		std::string titulo_pelicula;
		std::string fecha;
		std::string hora_de_inicio;

		std::istringstream f(funcion_str);

		std::getline(f, id_sala, ',');
		std::getline(f, titulo_pelicula, ',');
		std::getline(f, fecha, ',');
		std::getline(f, hora_de_inicio, ',');

		if (!salas.exist(id_sala)) {
			std::stringstream ss;
			ss << "La sala "
			   << id_sala 
			   << " no existe en el sistema.";
			throw std::logic_error(ss.str());
		}

		if (!peliculas.exist(titulo_pelicula)) {
			std::stringstream ss;
			ss << "La película "
			   << titulo_pelicula 
			   << " no existe en el sistema.";
			throw std::logic_error(ss.str());
		}

		funcion.set_id(id);	
		funcion.set_id_sala(id_sala);          
		funcion.set_titulo_pelicula(titulo_pelicula);
		funcion.set_fecha(fecha);
		funcion.set_hora_de_inicio(hora_de_inicio);

		funciones.add(funcion);

		++id;
	}
}

/* Parametros
 * argv[1] = <puerto>
 * argv[2] = <salas.csv>
 * argv[3] = <peliculas.csv>
 * argv[4] = <funciones.csv>
 */ 

int main(int argc, char* argv[]) try {
	if ((argc - 1) != 4) 
		throw std::invalid_argument(std::string(
		"Uso: ./server <puerto> <salas.csv> <peliculas.csv> <funciones.csv>"));

	Salas salas;
	Peliculas peliculas;
	Funciones funciones;

	parse_salas_file(salas, argv[2]);
	parse_peliculas_file(peliculas, argv[3]);
	parse_funciones_file(funciones, peliculas, salas, argv[4]);
	
	Socket skt_acceptor;
	skt_acceptor.bind(strtol(argv[1], nullptr, 10));
	skt_acceptor.listen(MAX_STANDBY_CONNS);

	Acceptor acceptor(skt_acceptor, salas, peliculas, funciones);

	acceptor.start();

	while (true) if (std::cin.get() == 'q') {
		skt_acceptor.shutdown();
		break;
	}

	acceptor.join();

    return 0;
}
catch(const std::invalid_argument &e) {
	std::cerr << e.what() << std::endl;
	return 1;
}
catch(const std::logic_error &e) {
	std::cerr << e.what() << std::endl;
	return 2;
}
catch(const std::runtime_error &e) {
	return 1;
}
catch(...){}
