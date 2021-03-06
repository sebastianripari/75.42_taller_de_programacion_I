#ifndef __CACHE_DIRECT_H__
#define __CACHE_DIRECT_H__

/**** Memoria Cache ****/
/****    Directo    ****/

#include <string>
#include <vector>
#include "cache.h"

class Cache_direct: public Cache {
	std::vector<int> blocks;
	std::vector<bool> blocks_valid;

public:
	// Inicializa la memoria cache con el tamanio "size", pasado como parametro,
	// con bloques de tamanio "line_size" pasado como parametro.
	Cache_direct(const unsigned int size, const unsigned int line_size);
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
	~Cache_direct();
};

#endif
