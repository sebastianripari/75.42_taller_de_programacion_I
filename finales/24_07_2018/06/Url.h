#ifndef __URL_H__
#define __URL_H__

#include <string>
#include <iostream>
#include <sstream>

class Url {
	std::string protocolo;
	std::string host;
	int port;
	std::string file;

public:
	Url(std::string protocolo, std::string host, int port, std::string file);
	Url& operator=(Url&& other);
	bool operator==(Url& other);
	void operator>>(std::ostream& os);
	const std::string& get_protocolo() const;
	const std::string& get_host() const;
	int get_port() const;
	const std::string& get_file() const;
};

#endif
