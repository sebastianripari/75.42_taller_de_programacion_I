#ifndef __CACHE_ASSOCIATIVE_FIFO_H__
#define __CACHE_ASSOCIATIVE_FIFO_H__

/****  Memoria Cache  ****/
/**** Asociativo FIFO ****/

#include <string>
#include "cache.h"
#include "deque.h"

class Cache_fa_fifo: public Cache {
	Deque blocks;

public:
	// Inicializa la memoria cache con el tamanio "size", pasado como parametro,
	// con bloques de tamanio "line_size" pasado como parametro.
	Cache_fa_fifo(const unsigned int size, const unsigned int line_size);
	// Accede a la direccion de memoria pasada como parametro, 
	// si el bloque correspondiente a esta direccion se encuentra
	// en la memoria cache se retorna HIT(1), caso contrario se retorna MISS(2).
	// Si la direccion es invalida se retorna ERROR(-1).
	// El metodo es thread safe.
	int access(const std::string &address);
	// Retorna la cantidad de misses.
	unsigned int get_misses() const;
	// Retorna la cantidad de hits.
	unsigned int get_hits() const;
	// Libera los recursos utilizados.
	~Cache_fa_fifo();
};

#endif
