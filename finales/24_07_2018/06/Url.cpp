#include "Url.h"

Url::Url(std::string protocolo, std::string host, int port, std::string file)
	: protocolo(protocolo),
	  host(host),
	  port(port),
	  file(file) {}

Url& Url::operator=(Url&& other) {
	if(this == &other) return *this;
	this->protocolo = other.protocolo;
	this->host = other.host;
	this->port = other.port;
	this->file = other.file;
	return *this;
}	

bool Url::operator==(Url& other) {
	if(	(this->protocolo == other.protocolo) &&
		(this->host == other.host) &&
		(this->port == other.port) &&
		(this->file == other.file)) return true;
	return false;
}

void Url::operator>>(std::ostream& os) {	
    os << "Protocolo: " << this->get_protocolo() << std::endl 
       << "Host: " << this->get_host() << std::endl 
       << "Port: " << this->get_port() << std::endl 
       << "File: " << this->get_file() << std::endl; 
}

const std::string& Url::get_protocolo() const {
	return this->protocolo;
}

const std::string& Url::get_host() const {
	return this->host;
}

int Url::get_port() const {
	return this->port;
}

const std::string& Url::get_file() const {
	return this->file;
}


