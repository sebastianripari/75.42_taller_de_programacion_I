/*
Enunciado.
Como se logra que 2 threads accedan (lectura/escritura)
a un mismo recurso compartido sin que se genere problemas
de consistencia? Ejemplifique
*/

#include <iostream>
#include <thread>
#include <mutex>

class Int_protected {
	int i;
	std::mutex m;

public:
	Int_protected() : i(0) {}

	int incrementar() {
		this->m.lock();
		++i;
		int r = i;
		this->m.unlock();
		return r;
	}

	int get() {
		this->m.lock();
		int r = i;
		this->m.unlock();
		return r;
	}
};

void sumador(Int_protected* i) {
	while(true) {
		if(i->incrementar() == 1000) break;
	}
}
 
int main() {
	Int_protected i;

	std::thread thread_sumador(&sumador, &i);

	while(true) {
		int j = i.get();
		std::cout << j << std::endl;
		if(j == 1000) break;
	}

	thread_sumador.join();

	return 0;
}