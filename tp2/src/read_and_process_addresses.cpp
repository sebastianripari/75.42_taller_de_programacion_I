#include <string>
#include <iostream> 
#include <sstream>
#include "thread.h"
#include "input.h"
#include "read_and_process_addresses.h"

#define ERROR -1
#define HIT    1
#define MISS   2

void Read_and_process_addresses::run() {
	Input addresses;
	std::string address;
	addresses.open_file(this->path);
	while(addresses.get_line(address)) {
		int response = this->cpu.access(address);
		if(response == ERROR) {
			std::stringstream output_err;
			output_err << "Direccion invalida: "
	                   << address
	                   << std::endl
	                   << "Abortando"
	                   << std::endl;
	        this->cerr.cerr(output_err.str());
	        break;
	    }
		if(this->debug) {
			std::stringstream output;
			if      (response == HIT)  output << "Hit: ";
			else if (response == MISS) output << "Miss: ";

			std::locale loc;
			for (std::string::size_type i=0;
				i<address.length();
				++i) output << std::tolower(address[i],loc);
			output << std::endl;
			this->cout.cout(output.str());
		}
	}
}
   
void Read_and_process_addresses::operator()() {
	this->run();  
}
