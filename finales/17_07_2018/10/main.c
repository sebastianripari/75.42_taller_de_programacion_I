/*
Describa el proceso de transformacion de codigo fuente a un ejecutable.
Precise las etapas y las tareas desarrolladas en cada una de ellas.
*/

/*
Condigo Fuente -> Compilacion -> Codigo Ejecutable.

// Compilacion.
1) Precompilacion. 
2) Compilacion.
3) Linkedicion.

// Precompilacion.
Aqui es cuando se ejecutan las directivas de preprocesador.
Las identificamos porque empiezan con numeral (#).
Ejemplos: #define #elif #else #endif #include.
Observacion: Terminada esta etapa ya no existen los headers,
debido a que le preprocesador los incluyo en los .c o .cpp.

// Compilacion.
1) Parser.
2) Traduccion.
3) Ensamblado.

// Parser
Aqui se lleva a cabo el reconocimiento de la sintaxis.
Se mira que sea correcta.
// Traduccion.
Se traduce el codigo a lenguaje en ensamblador.
// Ensamblado
Se tranduce de lenguaje ensamblador a codigo binario.

// Linkedicion
Es el que une los diferentes binary files, para lograr el ejecutable final.
Por ejemplo un binary file tiene la definicion de una funcion que se usa 
en otro binary file, entonces esos dos binarios van a ser unidos.
*/

int main() {
	Persona ;
	return 0;
}