/*
Enunciado.
Escribir un programa ANSI C que, sin crear archivos intermedios,
altere el archivo “a.txt” reemplazando todas las secuencias “-” por “--”.
*/

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int leer_reversa(char* c, FILE* f, int* seek) {
	int continuar = 1;
	if(*seek == 0) continuar = 0;
	fseek(f, *seek, SEEK_SET);
	*c = fgetc(f);
	fseek(f, - (2 * sizeof(char)), SEEK_CUR);
	*seek = ftell(f);
	return continuar;
}

void escribir_reversa(char c, FILE* f, int* seek) {
	fseek(f, *seek, SEEK_SET);
	fputc(c, f);
	fseek(f, - (2 * sizeof(char)), SEEK_CUR);
	*seek = ftell(f);
}

void armar_archivo() {
	FILE* f = fopen("a.txt", "w");
	char caracteres[] = "sebastian-daniel-ripari\0";
	fwrite(&caracteres, sizeof(char), strlen(caracteres), f);
	fclose(f);
}

void leer_archivo() {
	FILE* f = fopen("a.txt", "r");
	char c;
	while(fread(&c, sizeof(char), 1, f) == 1) printf("%c", c);
	printf("\n");
	fclose(f);
}

int agrandar_archivo() {
	FILE* f = fopen("a.txt", "r+");
	int c = 0;
	int contador = 0;
	int contador_guines = 0;
	while(!feof(f)) {
		c = fgetc(f);
		++contador;
		if(c == '-') ++contador_guines;
	}
	int size_original = sizeof(char) * contador;
	int size = sizeof(char) * (contador + contador_guines);
	ftruncate(fileno(f), size);
	fclose(f);
	return size_original;
}

void parsear_archivo(int size_original) {
	FILE* f = fopen("a.txt", "r+");
	fseek(f, size_original - sizeof(char), SEEK_SET);
	int seek_lectura = ftell(f);
	fseek(f, - sizeof(char), SEEK_END);
	int seek_escritura = ftell(f);
	char c = 0;
	while(leer_reversa(&c, f, &seek_lectura)) {
		escribir_reversa(c, f, &seek_escritura);
		if(c == '-') escribir_reversa(c, f, &seek_escritura);
	}
	fclose(f);
}

int main() {
	armar_archivo();
	int size_original = agrandar_archivo();
	parsear_archivo(size_original);
	leer_archivo();
	return 0;
}