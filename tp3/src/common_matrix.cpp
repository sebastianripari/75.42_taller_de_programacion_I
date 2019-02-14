#include "common_matrix.h"

Matrix::Matrix() {
	this->matrix = nullptr;
	this->filas = 0;
	this->columnas = 0;
}

Matrix::Matrix(const unsigned int filas, const unsigned int columnas) {
	this->matrix = new char[filas * columnas];
	for (unsigned int i=0; i< (filas * columnas); ++i) this->matrix[i] = 'O';
	this->filas = filas;
	this->columnas = columnas;
} 

Matrix::~Matrix() {
	if (this->matrix != nullptr) delete[] this->matrix;
}

Matrix& Matrix::operator=(Matrix&& other) {
	if (this == &other) return *this;
	this->filas = other.filas;
	this->columnas = other.columnas;
	if(this->matrix != nullptr) 
		delete [] this->matrix;
	this->matrix = other.matrix;
	other.matrix = nullptr;
	return *this;
}

bool Matrix::set(const unsigned int fila, const unsigned int columna) {
	unsigned int col = columna-1;

	unsigned int pos = 0;

	for(unsigned int i=0; i<fila; ++i) pos = pos + this->columnas;

	pos = pos + col;

	if(this->matrix[pos] == 'X') {
		return false;	
	} else {
		this->matrix[pos] = 'X';
		return true;
	}
}

const char 
Matrix::get(const unsigned int fila, const unsigned int columna) const {
	unsigned int pos = 0;

	for(unsigned int i=0; i<fila; ++i) pos = pos + this->columnas;

	pos = pos + columna;

	return this->matrix[pos];
}

bool Matrix::full() const {
	for(unsigned int i=0; i < this->filas * this->columnas; ++i)
		if (this->matrix[i] == 'O') return false;
	return true;
}

const unsigned int Matrix::get_cantidad_de_filas() const {
	return this->filas;
}

const unsigned int Matrix::get_cantidad_de_columnas() const {
	return this->columnas;
}
