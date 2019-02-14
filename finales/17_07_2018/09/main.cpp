/*
Enunciado.
Indique la salida del siguiente programa:

class A {
	A() {
		cout<< "A()" << endl;
	}

	~A(){
		cout<< "~A()" << endl;
	}
}

class B : public A {
	B() {
		cout<< "B()" << endl;
	}

	~B() {
		cout<< "~B()" << endl;
	}
}

int main() {
	B b;
	return 0;
}
*/

#include <iostream>

class A {
public:
	A() {
		std::cout<< "A()" << std::endl;
	}

	~A(){
		std::cout<< "~A()" << std::endl;
	}
};

class B : public A {
public:
	B() {
		std::cout<< "B()" << std::endl;
	}

	~B() {
		std::cout<< "~B()" << std::endl;
	}
};

int main() {
	B b;
	/*
	1) Se construye A.
	2) Se construye B.
	3) Se destruye B.
	4) Se destruye A.

	Por lo tanto la salida es:
	A()
	B()
	~B()
	~A()
	*/
	return 0;
}