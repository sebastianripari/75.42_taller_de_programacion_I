#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define STATE_INICIO 0
#define STATE_BARRA 1
#define STATE_ENTRE_PARENTESIS 2

int leer(char* c, long int* seek, FILE* f) {
	fseek(f, *seek, SEEK_SET);
	*c = fgetc(f);
	*seek = ftell(f);
	return !feof(f);
}

void escribir(char c, long int* seek, FILE* f) {
	fseek(f, *seek, SEEK_SET);
	fputc(c, f);
	*seek = ftell(f);
}

void parsear_archivo() {
	FILE* f = fopen("a.txt", "r+");
	int count = 0;
	char c = 0;
	long int seek_lectura = 0;
	long int seek_escritura = 0;
	int state = STATE_INICIO;
	while(leer(&c, &seek_lectura, f)) {
		++count;
		switch(state) {
			case STATE_INICIO:
				if(c == '/') state = STATE_BARRA;
				else {
					if(c == '(') state = STATE_ENTRE_PARENTESIS;
					escribir(c, &seek_escritura, f);
				}
				break;
			case STATE_BARRA:
				if(c == '/') {
					--count;
					escribir('*', &seek_escritura, f);
				} else {
					escribir('/', &seek_escritura, f);
					escribir(c, &seek_escritura, f);
				}
				state = STATE_INICIO;
				break;
			case STATE_ENTRE_PARENTESIS:
				if(c == ')') state = STATE_INICIO;
				escribir(c, &seek_escritura, f);
				break;
		}
	}
	ftruncate(fileno(f), sizeof(char) * count);
	fclose(f);
}

void armar_archivo() {
	FILE* f = fopen("a.txt", "w");
	char caracteres[] = "//Sebastian//Daniel//Ripari//(//96453//)\0";
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

int main() {
	armar_archivo();
	parsear_archivo();
	leer_archivo();
	return 0;
}