/*
Se tiene un archivo binario de enteros de 4 bytes.
Se pide duplicar los enteros que sean multiplos de 5.
*/

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include <stdio.h>

#define SIZE_OF_INT 4

void armo_archivo() {
	FILE* f = fopen("numeros", "wb");
	int i;
	i = 3;
	fwrite(&i, SIZE_OF_INT, 1, f);
	i = 4; 
	fwrite(&i, SIZE_OF_INT, 1, f);
	i = 0; 
	fwrite(&i, SIZE_OF_INT, 1, f);
	i = 33;
	fwrite(&i, SIZE_OF_INT, 1, f);
	i = 15;
	fwrite(&i, SIZE_OF_INT, 1, f);
	i = 22;
	fwrite(&i, SIZE_OF_INT, 1, f);
	i = 41;
	fwrite(&i, SIZE_OF_INT, 1, f);
	i = 0;
	fwrite(&i, SIZE_OF_INT, 1, f);
	i = 5;
	fwrite(&i, SIZE_OF_INT, 1, f);
	i = 1;
	fwrite(&i, SIZE_OF_INT, 1, f);
	fclose(f);
}

void leer_archivo() {
	FILE* f = fopen("numeros", "rb");
	int i;
	while(fread(&i, SIZE_OF_INT, 1, f) == 1)
		printf("%i\n", i);
	fclose(f);
}

int agrandar_archivo() {
	FILE* f = fopen("numeros", "r+b");
	int i;
	int contador = 0;
	int contador_multiplos_cinco = 0;
	while(fread(&i, SIZE_OF_INT, 1, f) == 1) {
		++contador;
		if(i % 5 == 0) ++contador_multiplos_cinco;
	}
	int size = (contador + contador_multiplos_cinco) * SIZE_OF_INT;
	int size_original = contador * SIZE_OF_INT;
	ftruncate(fileno(f), size);
	fclose(f);
	return size_original;
}

int leer_reversa(int* i, int* seek, FILE* f) {
	int continuar;
	if(*seek == 0) continuar = 0;
	else continuar = 1; 
	fseek(f, *seek, SEEK_SET);
	fread(i, SIZE_OF_INT, 1, f);
	fseek(f, - (SIZE_OF_INT * 2), SEEK_CUR);
	*seek = ftell(f);
	return continuar;
}

void escribir_reversa(int i, int* seek, FILE* f) {
	fseek(f, *seek, SEEK_SET);
	fwrite(&i, SIZE_OF_INT, 1, f);
	fseek(f, -(SIZE_OF_INT * 2), SEEK_CUR);
	*seek = ftell(f);
}

void duplicar_multiplos_cinco(int size_original) {
	FILE* f = fopen("numeros", "r+b");
	fseek(f, size_original - SIZE_OF_INT, SEEK_SET);
	int seek_lectura = ftell(f);
	fseek(f, -SIZE_OF_INT, SEEK_END);
	int seek_escritura = ftell(f);
	int i;
	while(leer_reversa(&i, &seek_lectura, f)) {
		escribir_reversa(i, &seek_escritura, f);
		if(i % 5 == 0) escribir_reversa(i, &seek_escritura, f);
	}
	fclose(f);
}

int main() {
	armo_archivo();
	int size_original = agrandar_archivo();
	duplicar_multiplos_cinco(size_original);
	leer_archivo();
	return 0;
}