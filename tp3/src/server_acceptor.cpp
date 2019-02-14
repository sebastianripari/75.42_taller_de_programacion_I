#include <iomanip>
#include <set>
#include <iostream>

#include "server_requests_handler.h"
#include "server_acceptor.h"
#include "common_socket.h"
#include "common_constants.h"

void Acceptor::run() {
	std::set<Thread*> threads;
	try {
		while(true) {
			Socket socket = this->skt_acceptor.accept();
			Requests_handler *requests_handler = new Requests_handler(
				std::move(socket),
				salas, 
				peliculas,
				funciones);
			threads.insert(requests_handler);
			requests_handler->start();
			this->garbage_collector(threads);
		}
	}
	catch (...) {
		// Cuando el thread que corre el server main hace
		// un shutdown del Socket Acceptor, este que estaba bloqueado en
		// el accept(), arroja una excepcion
		// (std::runtime_error, ver documentacion de common_socket.h).
		// Esta excepcion la capturamos aqui para que salga del bucle. 
	}

	for (Thread* thread : threads)        thread->join();
	for (Thread* thread : threads) delete thread;
}

void Acceptor::garbage_collector(std::set<Thread*> &threads) {
	std::set<Thread*> threads_to_erase;
	for (Thread* thread : threads) {
		if(((Requests_handler*) thread)->get_is_dead()) {
			thread->join();
			delete thread;
			threads_to_erase.insert(thread);
		}
	}
	for (Thread* thread : threads_to_erase) threads.erase(thread);
}
   
void Acceptor::operator()() {
	this->run();  
}
