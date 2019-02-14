#ifndef __LOCK_H_
#define __LOCK_H_

/**** Wrapper de std::mutex ****/

/* El principal objetivo de este Wrapper es 
 * es aplicar el concepto RAII */
 
#include <mutex>

class Lock {
private:
	std::mutex &m;

public:
	explicit Lock(std::mutex &m) : m(m) {
		m.lock();
	}

	~Lock() {
		m.unlock();
	}

private:
	// Prohibimos la construccion por copia.
	Lock(const Lock&) = delete;
	// Prohibimos la construccion por movimiento.
	Lock(Lock&&) = delete;
	// Prohibimos la asignacion por movimiento.
	Lock& operator=(Lock&&) = delete;
	// Prohibimos la asignacion. 
	Lock& operator=(const Lock&) = delete;
};

#endif
