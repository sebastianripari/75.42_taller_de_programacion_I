/*
Implemente la funcion void String_a_Int(char *bin, int *ent)
que interprete la cadena bin (de 32 1s/0s) y guarde el valor
correspondiente en el entero indicado por ent.
*/

#include <stdio.h>

void String_a_Int(char *bin, int *ent) {
	for (int i = 0; i < 32; ++i) {
        *ent = *ent << 1;
        *ent = *ent + (bin[i] - '0');
    }
}

int main() {
	// 32 Bits
	char bin[33] = "00000000000000000000000000100111\0";
	int ent = 0;
	String_a_Int(bin, &ent);
	
	printf("%i\n", ent);

	return 0;
}