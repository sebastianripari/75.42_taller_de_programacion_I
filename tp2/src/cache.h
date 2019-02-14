#ifndef __CACHE_H__
#define __CACHE_H__

/**** Memoria Cache ****/

// Es una clase abstracta, tiene todos sus metodos virtuales puros.

#include <math.h>
#include <mutex>
#include <string>

class Cache {
protected:
	unsigned int size;      // bytes
	unsigned int line_size; // bytes
	unsigned int n_blocks;

	bool debug;

	std::mutex m;

	unsigned int misses;
	unsigned int hits;

	// Informa si una direccion es valida.
	// Retorna 'true' si es valida, 'false' sino.
	bool is_valid(const int address) {
		if (address % 4 == 0) return true;
		else                  return false;      
	}

	// Extrae el tag de una direccion.
	// Retorna el tag.
	int get_tag(const int address) {
		unsigned int bits_offset = log2(this->line_size);
		return address >> bits_offset;
	}

public:
	// Accede a la direccion de memoria pasada como parametro, 
	// si el bloque correspondiente a esta direccion se encuentra
	// en la memoria cache se retorna HIT(1), caso contrario se retorna MISS(2).
	// Si la direccion es invalida se retorna ERROR(-1).
	// El metodo es thread safe.
	virtual int access(const std::string &address) = 0;
	// Retorna la cantidad de misses.
	virtual unsigned int get_misses() const = 0;
	// Retorna la cantidad de hits.
	virtual unsigned int get_hits() const = 0;
	// Libera los recursos utilizados.
	virtual ~Cache() {}
};

#endif
