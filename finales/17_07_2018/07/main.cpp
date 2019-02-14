#include <list>
#include <iostream>

template <class T>
std::list<T> SinSegunda(std::list<T> a, std::list<T> b) {
	std::list<T> l;
	for(auto& it_a : a) {
		bool esta_en_b = false;
		for(auto& it_b : b) {
			if(it_a == it_b) {
				esta_en_b = true;
			}
		}
		if(!esta_en_b) l.push_front(it_a);
	}
	return l;
}
int main() {
	// Ejemplo de uso de la funcion SinSegunda.
	std::list<int> a;
	std::list<int> b;

	a.push_front(4);
	a.push_front(5);
	a.push_front(6);
	a.push_front(7);

	b.push_front(5);
	b.push_front(4);

	std::cout << SinSegunda(a, b).size() << std::endl;

	return 0;
}