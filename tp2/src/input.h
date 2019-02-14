#ifndef __INPUT_H__
#define __INPUT_H__

/**** Entrada estandar o un archivo especico ****/

#include <fstream> 
#include <string>

class Input {
	std::ifstream input;

public:
	// Abre el archivo que se encuentra donde especifica el parametro.
	void open_file(char *path);
	// Obtiene una linea del archivo o de la entrada estandar segun corresponda
	// Post: la linea obtenida es guardada en el parametro,
	//       retorna true si puedo obtenerla, y false caso contrario.
	bool get_line(std::string &line);
	// Si es el caso en que abrio un archivo, lo cierra.
	~Input();
};

#endif
