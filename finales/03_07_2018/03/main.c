/*
Enunciado.
Escribir un programa que procese un archivo binario de enteros
sin signo sobre si mismo. El procesamiento consiste en leer
pares de enteros de 1 byte cada uno y reemplazarlos por 3 enteros
(el archivo se agranda): su suma, su resta y el OR logico entre ambos.
*/

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>

void make_file() {
	FILE* f = fopen("a", "w");
	fputc('2', f);
	fputc('2', f);
	fputc('6', f);
	fputc('8', f);
	int i = 31;
	fputc(i + '0', f);
	i = 14;
	fputc(i + '0', f);
	fclose(f);
}

void read_file() {
	FILE* f = fopen("a", "r");
	char c;
	while((c = fgetc(f)) != EOF) printf("%i\n", c - '0');
	fclose(f);
}

bool expand_file(int* size_original) {
	FILE* f = fopen("a", "r+");
	int count = 0;
	int c;
	while((c = fgetc(f)) != EOF) ++count;
	*size_original = count * sizeof(char);
	int size = (count + (count / 2)) * sizeof(char);
	ftruncate(fileno(f), size);
	fclose(f);
	if((count % 2) != 0) {
		printf("Error: Cantidad impar de numeros.\n");
		return false;
	}
	else return true;
}

bool read_reverse(FILE* f, char* c,int* seek) {
	bool seguir;
	if(*seek == 0) seguir = false;
	else seguir = true;
	fseek(f, *seek, SEEK_SET);
	*c = fgetc(f);
	fseek(f, -(2 * sizeof(char)), SEEK_CUR);
	*seek = ftell(f); 
	return seguir;
}

void write_reverse(FILE* f, char c, int* seek) {
	fseek(f, *seek, SEEK_SET);
	fputc(c, f);
	fseek(f, -(2 * sizeof(char)), SEEK_CUR);
	*seek = ftell(f); 
}

void parser(int size_original) {
	FILE* f = fopen("a", "r+");
	fseek(f, size_original - sizeof(char), SEEK_SET);
	int seek_read = ftell(f);
	fseek(f, -sizeof(char), SEEK_END);
	int seek_write = ftell(f);
	bool seguir;
	char i;
	char j;
	do {
		read_reverse(f, &i, &seek_read);
		seguir = read_reverse(f, &j, &seek_read);
		char suma = ((i - '0') + (j - '0')) + '0';
		char resta = ((i - '0') - (j - '0')) + '0';
		char or = ((i - '0') | (j - '0')) + '0';
		write_reverse(f, or, &seek_write);
		write_reverse(f, resta, &seek_write);
		write_reverse(f, suma, &seek_write);
	} while(seguir);
	fclose(f);
}

int main() {
	make_file();
	int size_original;
	if(!expand_file(&size_original)) return -1;
	parser(size_original);
	read_file();
	return 0;
}