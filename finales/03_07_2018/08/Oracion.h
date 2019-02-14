class Oracion {
	char* str;

public:
	// Constructor default.
	Oracion();
	// Constructor por copia.
	Oracion(const Oracion& other);
	// Operador Suma.
	char* operator+(const Oracion& other);
	// Operador Resta.
	char* operator-(const Oracion& other);
	// Opereador Asignacion por Copia.
	Oracion& operator=(const Oracion& other);
};