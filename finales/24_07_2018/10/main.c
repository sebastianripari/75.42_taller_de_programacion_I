#include <stddef.h>
#include <stdio.h>

int f() {
	return 0;
}

// unsigned = unsigned int (Es simplemente una abreviatura)
// short = short int (Es simplemente una abreviatura)
// "B" es una funcion que recibe dos parametros, un unsigned int y un short int. 
// Y retorna un puntero a char.
char* B(unsigned a, short b) {
	char* c = NULL;
	return c;
}

int main() {
	// "p" es una variable que almacena el puntero a una
	// funcion que no recibe parametros y retorna un int.
	int (*p)();

	// Ejemplo de uso.
	p = &f;
	p();
	
	static unsigned **C[3];

//					  C    C
//					 *C    C es un puntero
//                  **C    C es un puntero a otro puntero
//         unsigned **C    C es un puntero a otro puntero que apunta a unsigned int
//  static unsigned **C	   C es un puntero a otro puntero que apunta a unsigned int estatico
//  static unsigned **C[3] C es un array de: puntero que apunta a otro puntero que apunta a un unsigned int estatico.
	
	// Ejemplo de uso.
	static unsigned int v = 3;
	static unsigned int* w = &v;
	static unsigned int** z = &w; 
	C[0] = z;
	printf("%i\n", **C[0]);
   
	return 0;
}