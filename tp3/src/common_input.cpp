#include <iostream> 
#include <string>
#include "common_input.h"

void Input::open_file(const char *path) {
	this->input.open(path);
}

bool Input::is_open() {
	return this->input.is_open();
}

bool Input::get_line(std::string &line) {
	if (this->input.is_open()) std::getline(this->input, line);
	else 					   std::getline(std::cin   , line);
	
	return line.empty() ? false : true;
}

Input::~Input() {
	if (this->input.is_open()) this->input.close();
}
