/*
Enunciado: Que es un deadlock? Ejemplifique.
*/

/*
Definicion de Deadlock.
Es un estado en el cual cada thread 
esta a la espera de que el otro le 
libere un recurso que necesita para
continuar su ejecucion. Entonces todos 
ellos quedan trabados.
*/

#include <mutex>
#include <thread>
#include <iostream>

std::mutex m;
void print(std::string s) {
	m.lock();
	std::cout << s << std::endl;
	m.unlock();
}

std::mutex m1;
std::mutex m2;

void f() {
	print("f locking m1");
    m1.lock();
    print("f locked m1");
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    print("f locking m2");
	m2.lock(); 
	print("f locked m2");

	m1.unlock();
	m2.unlock();
}

void g() {
	print("g locking m2");
    m2.lock();
    print("g locked m2");
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    print("g locking m1");
    m1.lock();
    print("g locked m1");

    m2.unlock();
    m1.unlock();
}

int main() {
	// Ejemplo de Deadlock.
	std::thread t1(&f);
	std::thread t2(&g);
	t1.join();
	t2.join();
	return 0;
}