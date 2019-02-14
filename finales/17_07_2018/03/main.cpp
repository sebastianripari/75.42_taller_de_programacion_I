/*
Enunciado.
Que es una macro en C?
*/

/*
Macro es un fragmento de codigo con un nombre dado.
Ese nombre es un identificador para llamar a la macro.
Hay dos tipos de macros.

// Object-like Macros
Ejemplos:
#define NUMERO 3
#define BUFFER_SIZE 1024
foo = (char *) malloc (BUFFER_SIZE);

// Function-like Macros
#define min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define foo(x) x, "x"
*/

#include <iostream>
#define min(X, Y) (X < Y ? X : Y)
#define foo(x) x

int main() {
	std::cout << min(22, 13) << std::endl;
	std::cout << foo(5) << std::endl;
	return 0;
}