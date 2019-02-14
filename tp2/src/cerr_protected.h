#ifndef __CERR_PROTECTED_H__
#define __CERR_PROTECTED_H__

/**** (Monitor) Salida estandar de error ****/

#include <mutex>
#include <string>
#include "lock.h" 

class Cerr_protected {
	std::mutex m;

public:
	// Emite por salida estandar de error el string pasado por parametro.
	// Es thread safe.
	void cerr(const std::string &s) {
		Lock l(m);
		std::cerr << s;
	}
};

#endif
