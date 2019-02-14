/*
Enunciado.
Escriba una funcion de C llamada strncat_new que reciba tres parametros:
dos punteros a caracter constante (S1 y S2) y un entero sin signo (L).
La funcion debe concatenar S1 con S2 y retornar una nueva cadena de
caracteres considerando L como tamaño maximo para cualquiera de los
elementos (S1, S2 y la nueva cadena).
La funcion debe detectar condiciones de erro respecto de la longitud
y retornar NULL en cualquier caso.
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* strncat_new(const char* S1, const char* S2, unsigned int L) {
	int size_S1 = strlen(S1);
	if(size_S1 > L) return NULL;
	int size_S2 = strlen(S2);
	if(size_S2 > L) return NULL;
	if((size_S1 + size_S2) > L) return NULL;
	char* S = malloc(size_S1 + size_S2);
	strncat(S, S1, size_S1);
	strncat(S, S2, size_S2);
	return S;
}

int main() {
	// Ejemplo de uso.
	const char* S1 = "sebas";
	const char* S2 = "tian";
	char* S = strncat_new(S1, S2, 10);
	if(S != NULL) {
		printf("%s\n", S);
		free(S);
	}
	return 0;
}