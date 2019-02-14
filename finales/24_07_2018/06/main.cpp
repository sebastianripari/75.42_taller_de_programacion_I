/*
Defina la clase URL para permitir almacenar las siguientes propiedades:
protocolo (http), host (fi.uba.ar), port (80),
y file (index.php o resources/img/logo.png).

A su vez se pide que implemente los siguientes operadores: operator<<, operator==
y operator=.
*/

/*
Enunciado
Defina la clase URL para permitir almacenar las siguientes propiedades:
protocolo (http), host (fi.uba.ar), port (80), y file (index.php o resources/img/logo.png)
A su vez se pide que implemente los siguientes operadores: operator<<, operator==
y operator=.
*/

#include "Url.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Url& obj) {	
    os << "Protocolo: " << obj.get_protocolo() << std::endl 
       << "Host: " << obj.get_host() << std::endl 
       << "Port: " << obj.get_port() << std::endl 
       << "File: " << obj.get_file() << std::endl;  

    return os;
}

int main() {
	Url url("http", "fi.uba.ar", 80, "index.php");
	std::cout << url;
	std::cout << std::endl << std::endl;
	url >> std::cout;
	
	return 0;
}