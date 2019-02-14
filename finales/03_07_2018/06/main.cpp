/*
Cual es el motivo por el cual las clases que
utilizan templates se declaran y definen en los .h?
*/

/*
Todo el template debe ir en el .h para que el 
compilador pueda armar la clase en el momento
que se especifiquen los tipos genericos. Si las 
definiciones no se encuentran en el header, 
entonces el compilador cuando reciba el tipo y quiera
construir la clase con el tipo proporcionado, no podra hacerlo.
Especificamente es el linker el que no podra en enlazar la declaracion
de la funciones con las definiciones. 
Nota: Probar como no compila.
Recordar que un template no es una clase, sino que son instrucciones
para el que el compilador pueda hacer una clase con tipos genericos.
*/

#include "container.h"
//#include "contenedor.h"

int main() {
	Container<int> bag;
	//Contenedor<int> bag;
	bag.add(3);
	return 0;
}