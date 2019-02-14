/*
Enunciado
Escriba una funcion C llamada Agrandar que reciba por parametro 1 cadena (S),
dos indices (I1, I2) y una cantidad (Q).
La funcion debe retornar una copia de S salvo los caracteres entre los indices
I1 y I2 que seran duplicados Q veces en la misma posicion.
Ej: Agrandar("Chau", 1, 2, 3) retorna "Chahahau"
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* agrandar(char s[], int i1, int i2, int q) {
	int r_legth = (i1 - 0) + ((i2 - i1)*q) + (strlen(s) - i2);
	
	char* r = malloc(r_legth);

	int pos = 0;

	for(int i = 0; i < i1; ++i) {
		r[pos] = s[i];
		++pos;
	}

	for(int j = 0; j < q; ++j) {
		for(int i = i1; i <= i2; ++i) {
			r[pos] = s[i];
			++pos;
		}
	}

	for(int i = 1; (i + i2) < strlen(s); ++i) {
		r[pos] = s[i2 + i];
		++pos;
	}

	r[pos] = '\0';

	return r;
}

int main() {
	char s[10] = "Sebastian\0";
	char* r = agrandar(s, 2, 4, 2);
	printf("%s\n", r);
	free(r);
	return 0;
}

