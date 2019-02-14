#ifndef __READ_AND_PROCESS_ADDRESSES_H__
#define __READ_AND_PROCESS_ADDRESSES_H__

/* El functor Read_and_process_addresses toma direcciones de memoria
 * de un archivo, una por una, se las pasa el CPU, para que este acceda,
 * a ellas, mediante su memoria cache. Los resultados de estos accesos 
 * son sacados por un output.
 */

#include "cpu.h"
#include "cout_protected.h"
#include "cerr_protected.h"

class Read_and_process_addresses: public Thread {
	Cpu &cpu;
	Cout_protected &cout;
	Cerr_protected &cerr;
	char *path;
	bool debug;
public:
	Read_and_process_addresses(
		Cpu &cpu,
		Cout_protected &cout,
		Cerr_protected &cerr,
		char *path,
		bool debug
	) : cpu(cpu), cout(cout), cerr(cerr), path(path), debug(debug) {}
	// Corre la funcionalidad del functor.	
	void run();
    // Redefinimos el operador (). Para que llame a la funcion run. 
	void operator()();
};

#endif
