/*
Enunciado.
Explique la diferencia entre las etapas de compilacion y
enlazado (linking). Escriba un breve ejemplo de codigo
con errores para cada una de ellas indicandolos de forma clara.
*/

/*
Codigo Fuente -> Compilacion -> Ejecutable.

Pasos de Compilacion:
1) Precompilacion:
Se encarga de leer todas las instrucciones con numeral,
#define, #ifndef, #else, #endif. Cuando agarra clases con 
.h y .c los transforma en un .c que contiene todo, y sin 
ninguna instruccion de precompilacion, osea con #.

2) Compilacion:
Transforma los .c en .o, osea codigo binario.
Lo hace en 3 etapas
- Parseo: Reconoce la sintaxis.
- Traduccion: Traduce la sintaxis en instrucciones de lenguaje ensamblador.
- Ensamblado: Traduce el lenguaje ensamblador a codigo binario.

3) Linkedicion:
Une todos los .o y crea el binario final ejecutable.
*/

/*
Diferencias entre compilacion y linkedicion:
En la compilacion se chequean cosas como que la sintaxis este bien,
y en la linkedicion se chequea que las definiciones de las 
funciones/metodos que son llamados existan.
*/

/*
Ejemplo errores en la etapa de compilacion:
int main() {
	NumeroComplejo z;
	return 0;
}
Aqui el compiler arrojara el error "'NumeroComplejo' was not declared in this scope"
Como no conoce el tipo no sabe cuanta memoria reservarle a la variable "z".

Lo mismo pasa con una funcion
int main() {
	f(2, 3);
	return 0;
}

Ejemplo de errores en la etapa de linkedicion:
void f(int x, int y);

int main() {
	f(2, 3);
	return 0;
}

Aqui el error se da en la etapa de linkedicion 
undefined reference to `f(int, int)'. Ya que no puede
linkear la declaracion de la funcion "f" con la definicion 
de la misma porque no existe.
*/

void f(int x, int y);

int main() {
	// NumeroComplejo z;
	f(2, 3);
	return 0;
}