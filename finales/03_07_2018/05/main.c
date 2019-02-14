/*
Enunciado.
Dentro del siguiente codigo:

int main(int argc, char* argv[]) {

    return 0;

}

Defina:

a) Un puntero a entero sin signo a alocarse en el stack

b) Un arreglo para albergar 4 numeros de punto flotante que se aloque en el data segment.

c) Un caracter a alocarse en el data segment.
*/

/*
Una declaración introduce un identificador y describe su tipo,
ya sea un tipo, objeto o función. Una declaración es lo que 
el compilador necesita para aceptar referencias a ese identificador.
Estas son declaraciones:

extern int bar;
extern int g(int, int);
double f(int, double); // extern can be omitted for function declarations
class foo; // no extern allowed for type declarations

Una definición en realidad crea una instancia / implementa este identificador.
Es lo que necesita el enlazador para vincular las referencias a esas entidades.
Estas son definiciones correspondientes a las declaraciones anteriores:

int bar;
int g(int lhs, int rhs) {return lhs*rhs;}
double f(int i, double d) {return i+d;}
class foo {};
*/

#include <stdio.h>

int main(int argc, char* argv[]) {
	/* Definiciones */

	// Puntero a entero sin signo en el stack. 
	unsigned int* p;

	// Arreglo que alberga 4 numeros de punto
	// flotante en el data segment.
	static float numbers[4];

	// Caracter en el data segment.
	static char c;

	////////////////////////////////////////
	// Ejemplos de Uso.
	numbers[0] = 1.2;
	numbers[1] = 3.3;
	numbers[2] = 4.3;
	numbers[3] = 2.3;

	c = 'a';

	unsigned int i = 3;
	p = &i;

	printf("%i\n", *p);
	printf("%c\n", c);
	printf("%f\n", numbers[1]);

    return 0;
}