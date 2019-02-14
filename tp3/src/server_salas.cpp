#include <string>
#include "server_salas.h"
#include "common_lock.h"

bool
Salas::reservar(const std::string &id, const char f, const unsigned int c) {
	Lock l(this->m);

	for (Sala& sala : this->salas) 
		if (sala.get_id() == id) return sala.reservar(f, c);
	return false;
}

bool Salas::esta_agotada(const std::string &id) {
	Lock l(this->m);

	for (const Sala& sala : this->salas) 
		if (sala.get_id() == id) return sala.esta_agotada();
	return false;
}

void Salas::ver_asientos(
	const std::string &id_sala,
	std::string &asientos,
	bool &esta_agotada
) {
	Lock l(this->m);

	for (const Sala& sala : this->salas) {
		if (sala.get_id() == id_sala) {
			asientos = sala.ver_asientos();
			esta_agotada = sala.esta_agotada();
			return;
		}
	}

	throw std::runtime_error(std::string("id sala invalido"));
}

bool Salas::exist(const std::string &id) {
	for (const Sala& sala : this->salas)
		if (sala.get_id() == id) return true;
	return false;
}

void Salas::add(Sala &&sala) {
	this->salas.push_front(std::move(sala));
}
