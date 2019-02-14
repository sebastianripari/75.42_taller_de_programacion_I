#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__

/**** Acceptor ****/
/* Este functor es el que se encarga de
 * recibir a los nuevos clientes. */

#include <set>
#include "common_thread.h"
#include "common_socket.h"
#include "server_peliculas.h"
#include "server_funciones.h"
#include "server_salas.h"

class Acceptor: public Thread {
	Socket &skt_acceptor;
	Salas &salas;
	Peliculas &peliculas;
	Funciones &funciones;
public:
	Acceptor(
		Socket &skt_acceptor,
		Salas &salas,
		Peliculas &peliculas,
		Funciones &funciones
	) : 
		skt_acceptor(skt_acceptor),
		salas(salas),
		peliculas(peliculas),
		funciones(funciones) {}
	// Libera los recursos de aquellos threads que ya terminaron su trabajo.
	void garbage_collector(std::set<Thread*> &threads);
	// Corre la funcionalidad del functor.
	void run();
    // Redefinimos el operador (). Para que llame a la funcion run. 
	void operator()();
};

#endif
