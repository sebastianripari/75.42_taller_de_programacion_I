/*
Enunciado.
Escriba un programa C que reciba por argumento el nombre de un archivo
de numeros binarios de 16 bits y lo procese sobre si mismo.
El procesamiento consiste en repetir los numeros que sean "multiplos de 5 + 1" (6, 11, 16...)
(El archivo se agranda)
*/

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>

bool leer(FILE* f, short int* i, int* seek) {
	// Si llege al principio del archivo
	// ya no debo seguir.
	bool seguir;
	if (*seek == 0) seguir = false;
	else seguir = true;
	// Posiciono al archivo en el seek de lectura.
	fseek(f, *seek, SEEK_SET);
	// Leo un short int.
	fread(i, sizeof(short int), 1, f);
	// Retrocedo el seek de lectura.
	fseek(f, -(sizeof(short int) * 2), SEEK_CUR);
	*seek = ftell(f);
	return seguir;
}

void escribir(FILE* f, short int i, int* seek) {
	// Posiciono al archivo en el seek de escritura.
	fseek(f, *seek, SEEK_SET);
	// Escribo un short int.
	fwrite(&i, sizeof(short int), 1, f);
	// Recetrocedo el seek de escritura.
	fseek(f, -(sizeof(short int) * 2), SEEK_CUR);
	*seek = ftell(f);
}

void armo_file() {
	FILE* f = fopen("a", "wb");
	short int i;
	i = 2;
	fwrite(&i, sizeof(short int), 1, f);
	i = 3;
	fwrite(&i, sizeof(short int), 1, f);
	i = 5;
	fwrite(&i, sizeof(short int), 1, f);
	i = 2;
	fwrite(&i, sizeof(short int), 1, f);
	i = 600;
	fwrite(&i, sizeof(short int), 1, f);
	i = 44;
	fwrite(&i, sizeof(short int), 1, f);
	i = 22;
	fwrite(&i, sizeof(short int), 1, f);
	i = 1600;
	fwrite(&i, sizeof(short int), 1, f);
	i = 1;
	fwrite(&i, sizeof(short int), 1, f);
	fclose(f);
}

void print_file() {
	FILE* f = fopen("a", "rb");
	short int i;
	while(fread(&i, sizeof(short int), 1, f) == 1) printf("%hi\n", i);
	fclose(f);
}

int main() {
	// Armo el archivo con algunos numeros.
	armo_file();

	short int i;
	
	// Agrando el archivo.
	FILE* f = fopen("a", "r+b");
	int count = 0;
	while(fread(&i, sizeof(short int), 1, f) == 1) {
		++count;
		if((i % 5) == 0) ++count;
	}
	int size = sizeof(short int) * count;
	ftruncate(fileno(f), size);
	fclose(f);

	// Duplico a los multiplo de 5.
	f = fopen("a", "r+b");
	fseek(f, -2, SEEK_END);
	int seek_lectura = ftell(f);
	int seek_escritura = ftell(f);
	bool seguir;
	do {
		seguir = leer(f, &i, &seek_lectura);
		if(i != 0) {
			escribir(f, i, &seek_escritura);
			if((i % 5) == 0) escribir(f, i, &seek_escritura);
		}
	} while (seguir);
	fclose(f);

	// Imprimo el archivo.
	print_file();
	return 0;
}
