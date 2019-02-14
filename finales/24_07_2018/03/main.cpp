/*
Enunciado
Por que las librerias que usan Templates se publican con todo el
codigo fuente y no como un .h/.o
*/

/*
Las libs pensadas como templates tienen la obligacion de subir todo el codigo,
es decir las definiciones de las clases tambien, sin compilar, por el motivo de que
el parametro generico no esta definido, solo se conoce cuando el usuario lo especifica,
esto implica que la definicion solo se completa aqui. Para cada tipo va a haber una clase
diferente compilada por lo tanto no es posible tener un unico .o, por eso es que no se sube
compilada, sino que se compila solo cuando el usuario la usa bajo un tipo determinado,
asi que no queda otra que las libs asi, como por ejemplo STL, suban todo el codigo
para luego este se compile y se genere el .o cuando le especificamos el tipo.
*/

/* Bajar STL*/
// http://www.rrsd.com/software_development/stl/stl/download.html

#include "queue.h"

int main() {
	Queue<int> queue;
	return 0;
}
