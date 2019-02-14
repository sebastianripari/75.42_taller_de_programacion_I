/*
Enunciado
Que es la compilacion condicional?
En que etapa del proceso de transformacion de codigo se resuelve?
Ejemplifique mediante un codigo C dando un caso de uso util.
*/

/*
Compilacion condicional es cuando cierto bloque de
codigo se compila segun cierta condicion, que impone el 
programador. Se resuelve en la etapa de precompilacion.
*/

#include <stdio.h>
	
#define i 3

#if i == 3
void f() {
	printf("i == 3\n");
}
#else
void f() {
	printf("i != 3\n");
}
#endif

int main() {
	f();
	return 0;
}