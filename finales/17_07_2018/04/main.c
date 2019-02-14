char g(float* num, unsigned numbers[3]) {
	char c = 'a';
	return c;
}

int main() {
	// f es un puntero a una funcion que recibe 
	// un float y un array de unsigned. Y retorna
	// un char.
	char (*f)(float *, unsigned [3]);

	// Ejemplo de uso.
	f = &g;
	float number = 2.3;
	unsigned int numbers[3];
	numbers[0] = 0;
	numbers[1] = 1;
	numbers[2] = 2;
	f(&number, numbers);

	return 0;
}