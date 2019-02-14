#ifndef __REQUESTS_HANDLER_H__
#define __REQUESTS_HANDLER_H__

/**** Requests Handler ****/
/* Este functor es el encargado de manejar 
 * las peticiones de un cliente, el las recibe,
 * identifica el tipo, las procesa, y envia la respuesta.
 */ 

#include "common_thread.h"
#include "common_socket.h"
#include "server_peliculas.h"
#include "server_funciones.h"
#include "server_salas.h"

class Requests_handler: public Thread {
	Socket socket;
	Salas &salas;
	Peliculas &peliculas;
	Funciones &funciones;
	bool is_dead;
	
public:
	Requests_handler(
		Socket socket,
		Salas &salas,
		Peliculas &peliculas,
		Funciones &funciones
	) : 
		socket(std::move(socket)),
		salas(salas),
		peliculas(peliculas),
		funciones(funciones) {this->is_dead = false;}
	// Lista las peliculas de un idioma dado.
	void listar_por_idioma();
	// Lista las peliculas con una restriccion de edad dada.
	void listar_por_edad();
	// Lista las peliculas por un genero dado.
	void listar_por_genero();
	// Lista las funciones de una cierta fecha dada. 
	// Indica tambien si la funcion esta agotada.
	void listar_por_fecha();
	// Informa la disponibilidad de los asientos de una funcion dada.
	void ver_asientos();
	// Reserva en una funcion dada siempre y cuando alla disponibilidad.
	void reservar();
	// Corre la funcionalidad del functor.	
	void run();
	// Informa el estado de actividad del functor.
	// Retorna 'true' cuando ya no esta activo, es decir 
	// cuando termino su trabajo y esta listo para que se liberen sus recursos.
	// Caso contrario retorna 'false'.
	bool get_is_dead();
    // Redefinimos el operador (). Para que llame a la funcion run. 
	void operator()();
};

#endif
