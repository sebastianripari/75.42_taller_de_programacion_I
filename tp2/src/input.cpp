#include <fstream> 
#include <string>
#include "input.h"

void Input::open_file(char *path) {
	this->input.open(path);
}

bool Input::get_line(std::string &line) {
	if (this->input.is_open()) std::getline(this->input, line);
	
	return line.empty() ? false : true;
}

Input::~Input() {
	if (this->input.is_open()) this->input.close();
}
