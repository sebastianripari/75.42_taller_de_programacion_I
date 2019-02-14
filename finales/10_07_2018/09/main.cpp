/*
Enunciado.
Que es un thread?
Que funciones se utilizan para manipularlos (lanzarlos, etc)?
*/

/*
Un thread, es un hilo de ejecucion. Corre en paralelo. 
Los threads sirven, para ejecutar cosas en paralelo, y
asi lograr que un programa haga varias cosas a la ves.
*/

#include <thread>

void f() {
}

void g(int x){
}

void h(int x, int y) {
}

int main() {
	// Asi se lanzan los threads.
	std::thread t1(f);
	std::thread t2(g, 1);
	std::thread t3(h, 2, 3);

	// Asi se destruye un thread.
	// Esta funcion espera que el thread
	// termine su ejecucion. 
	t1.join();
	t2.join();
	t3.join();
	return 0;
}