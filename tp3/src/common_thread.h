#ifndef __THREAD_H__
#define __THREAD_H__

/**** Wrapper de std::thread ****/

#include <thread>

class Thread {
private:
	std::thread thread;
 
public:
	Thread();
	// Fired thread.	
	void start();
	/* El thread llamante se queda esperando en la llamada a este metodo hasta
	 * que el thread (this->thread) finalice la ejecucion de la funcion run.
	 */
	void join();
	// Funcion que correra el thread.
	virtual void run() = 0;
	// Prohibo construccion por copia.
	Thread(const Thread&) = delete;
	// Prohibo asignacion por copia.
    Thread& operator=(const Thread&) = delete;
	// Se destruyen todos los recursos asociados.
	virtual ~Thread();
};

#endif
