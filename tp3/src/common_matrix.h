#ifndef __MATRIX_H__
#define __MATRIX_H__

/*** Matriz ***/

class Matrix {
	char *matrix;
	unsigned int filas;
	unsigned int columnas;

public:
	// Construye la matriz. Inicializa sus atributos.
	Matrix();
	// Costruye la matriz en base a la cantidad 
	// de filas y columnas pasadas como parametro.
	// Inicializa todas las posiciones de la matriz con un 'O'.
	Matrix(const unsigned int filas, const unsigned int columnas);
	// Destructor. Libera los recursos usados.
	~Matrix();
	// Asignacion por movimiento.
	Matrix& operator=(Matrix&& other);
	// Prohibo la asignacion por copia.
	Matrix& operator=(const Matrix&) = delete;
	// Prohibo el contructor por copia.
	Matrix(const Matrix&) = delete;
	// Setea una 'X' en la fila y columna especificadas en los parametros.
	// Si en esa posicion ya habia una 'X' entonces retorna 'false',
	// si en cambio habia una 'O' retorna 'true.'
	bool set(const unsigned int fila, const unsigned int columna);
	// Informa si todas las posiciones logicas de la matriz poseen una 'X', 
	// en caso que pase esto retorna 'true', y si al menos hay una posicion con 
	// el caracter 'O' retorna 'false'.
	bool full() const;
	// Retorna el caracter almacenado en la matriz en la posicion especificada.
	const char get(const unsigned int fila, const unsigned int columna) const;
	// Retorna la cantidad de filas de la matriz.
	const unsigned int get_cantidad_de_filas() const;
	// Retorna la cantidad de columnas de la matriz.
	const unsigned int get_cantidad_de_columnas() const;
};

#endif
