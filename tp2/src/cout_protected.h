#ifndef __COUT_PROTECTED_H__
#define __COUT_PROTECTED_H__

/**** (Monitor) Salida estandar ****/

#include <mutex>
#include <string>
#include "lock.h" 

class Cout_protected {
	std::mutex m;

public:
	// Emite por salida estandar el string pasado por parametro.
	// Es thread safe.
	void cout(const std::string &s) {
		Lock l(m);
		std::cout << s;
	}
};

#endif
