/*
Enunciado.
Describa con exactitud las siguientes declaraciones/definiciones globales:

extern char (*l)[3];

static float *C[3];

static int F(const short *a);
*/

#include <stdio.h>

/*****************/
static int F(const short *a);
// F es una declaracion de funcion 
// que recibe un puntero a un const short int.
// Y retorna un static int.
/*****************/

static int F(const short *a) {
	static int b = 3;
	return b;
}

int main() {
	/*****************/
	static float *C[3];
// 	              C    C.
//               *C    C es un puntero.
//         float *C    C es un puntero a un float.
//  static float *C    C es un puntero a un float estatico.
//  static float *C[3] C es un array de 3 punteros a float estatico.

	// Ejemplo de uso.
	static float n_1 = 2.3;
	static float n_2 = 1.4;
	static float n_3 = 1.1;
	C[0] = &n_1;
	C[1] = &n_2;
	C[2] = &n_3;

	printf("%f\n", *C[0]);
	/*****************/
	/*****************/
	// Ejemplo de uso.
	const short int a = 1;
	F(&a);
	/*****************/

	return 0;
}