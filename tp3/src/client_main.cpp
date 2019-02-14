#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include "common_socket.h"
#include "common_input.h"
#include "common_constants.h"

unsigned int action_str_to_constant(const std::string &str) {
	if      (str == std::string("IDIOMA"))    return LISTAR_POR_IDIOMA;
	else if (str == std::string("EDAD"))      return LISTAR_POR_EDAD;
	else if (str == std::string("GENERO"))    return LISTAR_POR_GENERO;
	else if (str == std::string("FECHA"))     return LISTAR_POR_FECHA;
	else if (str == std::string("ASIENTOS"))  return VER_ASIENTOS;
	else if (str == std::string("RESERVA"))   return RESERVAR;
	else
		throw std::logic_error(std::string("Accion no reconocido"));
}

unsigned int str_to_unsigned_int(const std::string &str) {
	return (unsigned int) stoi(str, nullptr, 10);
}

/* Parametros
 * argv[1] = <ip-servidor>
 * argv[2] = <puerto-servidor>
 */ 

int main(int argc, char* argv[]) try {
	if ((argc - 1) != 2) 
		throw std::invalid_argument(
			std::string("Uso: ./client <ip-servidor> <puerto-servidor>"));

	Input input;
	Socket socket;

	socket.connect(argv[1], strtol(argv[2], nullptr, 10));

	std::string line, action;

	while(input.get_line(line)) {
		std::istringstream s(line);
		std::getline(s, action, ' ');
		socket.send_unsigned_int(action_str_to_constant(action));
		if (action == std::string("IDIOMA")) {
			std::string idioma; std::getline(s, idioma, '\n');
			socket.send_str(idioma + '\0');
		} else if (action == std::string("EDAD")) {
			std::string edad; std::getline(s, edad, '\n');
	        socket.send_str(edad + '\0');
		} else if (action == std::string("GENERO")) {
			std::string genero; std::getline(s, genero, '\n');
			socket.send_str(genero + '\0');
		} else if (action == std::string("FECHA")) {
			std::string dia, mes, anio;
			std::getline(s, dia, '/');
			std::getline(s, mes, '/');
			std::getline(s, anio, '/');
			socket.send_unsigned_int(str_to_unsigned_int(dia));
			socket.send_unsigned_int(str_to_unsigned_int(mes));
			socket.send_unsigned_int(str_to_unsigned_int(anio));
		} else if (action == std::string("ASIENTOS")) {
			std::string id_funcion; std::getline(s, id_funcion, '\n');
			socket.send_unsigned_int(str_to_unsigned_int(id_funcion));
		} else if (action == std::string("RESERVA")) {
			std::string id_funcion, fila, columna;
			std::getline(s, id_funcion, ' ');
			std::getline(s, fila, ' ');
			std::getline(s, columna, '\n');
			socket.send_unsigned_int(str_to_unsigned_int(id_funcion));
			socket.send_char(fila[0]);
			socket.send_unsigned_int(str_to_unsigned_int(columna));
		} 

		std::cout << socket.recv_str();
	}   
	
    return 0;
}
catch(const std::logic_error &e) {
	std::cerr << e.what() << std::endl;
	return 1;
}
catch(...) {
	return 1;
}
