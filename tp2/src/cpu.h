#ifndef __CPU_H__
#define __CPU_H__

/**** CPU ****/

#include <string>
#include "cache.h"

class Cpu {
	std::string vendor_id;
	std::string model_name;
	std::string frequency;
	Cache *cache;

public:
	Cpu();
	// Setea el vendedor del CPU. 
	void set_vendor_id(const std::string vendor_id);
	// Retorna el vendedor del CPU.
	const std::string & get_vendor_id() const;
	// Setea el modelo de CPU.
	void set_model_name(const std::string model_name);
	// Retorna el modelo del CPU.
	const std::string & get_model_name() const;
	// Setea la frecuencia del CPU.
	void set_frequency(const std::string frequency);
	// Retorna la frecuencia del CPU.
	const std::string & get_frequency() const;
	// Setea las especificaciones de la memoria Cache del CPU.
	// -- El primer parametro indica el tipo de cache:
	//  - Directo
	//  - Asociativo FIFO
	//  - Asociativo LRU
	// -- El segundo parametro indica el tamanio dela cache.
	// -- El tercer parametro indica el tamanio de un bloque de la cache. 
	void set_cache_specifications(
		const std::string type,
	    const unsigned int size,
	    const unsigned int line_size
	);
	// El CPU accede a la direccion de memoria pasada como parametro.
	// Busca esta direccion en la memoria cache.
	// Retorna:
	// -1: Si la direccion era invalida.
	//  1: Si fue un HIT en la cache.
	//  2: Si fue un MISS en la cache.
 	int access(const std::string & address);
 	// Devuelve la candidad de HITS realizados por la Cache.
	unsigned int get_cache_hits() const;
	// Devuelve la candidad de MISSES realizados por la Cache.
	unsigned int get_cache_misses() const;
	// Libera la memoria utilizada.
	~Cpu();
};

#endif
