/*
Enunciado
Escriba un programa que escriba por salida estandar los numeros entre
0 y 1000 ordenadamente. Se pide que los numeros pares sean escritos por un
hilo mientras los impares sean escritos por otro.
Contemple la correcta sincronizacion entre los hilos y la liberacion de los
recursos utilizados.
*/

#include <iostream>
#include <thread>
#include <condition_variable>

std::condition_variable cv;
std::mutex m;
bool main_working = true;

void imprimir_impares() {
	for(int i = 1; i <= 1000; i+=2) {
		{
			std::unique_lock<std::mutex> l(m);
    		cv.wait(l, []{return !main_working;});
			std::cout << i << std::endl;
			main_working = true;
		}
		cv.notify_one();
	}
}

int main() {
	std::thread t(imprimir_impares);

	for(int i = 0; i <= 1000; i+=2) {
		{
			std::unique_lock<std::mutex> l(m);
			cv.wait(l, []{return main_working;});
			std::cout << i << std::endl;
			main_working = false;
		}
    	cv.notify_one();
	}

	t.join();
}

