/*
Enunciado.
Explique que es y para que sirve un constructor MOVE en C++. Indique como
se comporta el sistema si este no es definido por el desarrollador.
*/

/*
Un constructor por movimiento es aquel que construye el objeto en base a 
otro, moviendo los atributos del otro hacia el. Sirve para mover objetos
de lugar, por ejemplo del stack de una funcion al stack de otra funcion, 
esto sin copiar, solo moviendo. 

Sino se define uno, entonces el sistema define uno por default,
que lo que hace es mover todos los atributos. 
*/

int main() {
	return 0;
}