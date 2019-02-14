#include <iostream> 
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "thread.h"
#include "input.h"
#include "cpu.h"
#include "read_and_process_addresses.h"
#include "cout_protected.h"
#include "cerr_protected.h"

#define SUCCESS 0

void parse_config_cpu(Cpu &cpu, Input &config, char *path, bool &debug) {
	config.open_file(path);

	std::string line;
	std::string key;
	std::string value;

	std::map<std::string, std::string> specs;
	
	while (config.get_line(line)) {
		std::istringstream s(line);
		std::getline(s, key, '=');
		std::getline(s, value, '\n');
		specs[key] = value;
	}

	unsigned int cache_size = 0;
	unsigned int cache_line_size = 0;

	cache_size = std::stoi(specs[std::string("cache size")]);
	cache_line_size = std::stoi(specs[std::string("line size")]);

	if (specs[std::string("debug")] == std::string("true")) debug = true;
	else                          							debug = false;

	cpu.set_vendor_id(specs[std::string("vendor_id")]);
	cpu.set_model_name(specs[std::string("model name")]);
	cpu.set_frequency(specs[std::string("cpu MHz")]);
	cpu.set_cache_specifications(
		specs[std::string("cache type")],
		cache_size,
		cache_line_size
	);

	std::cout << "# Cache Inicializada" <<                            std::endl    
			  << 											          std::endl;
}

void cout_cpu_specifications(const Cpu & cpu) {
	std::cout << "* Fabricante: "      << cpu.get_vendor_id()  <<      std::endl
	          << "* Modelo: "          << cpu.get_model_name() <<      std::endl
	          << "* Cpu MHz: "         << cpu.get_frequency()  <<      std::endl
	          <<                                                       std::endl;
}

void cout_cache_report(const Cpu & cpu) {
	std::cout <<                                                       std::endl
	          << "# Informe"           <<                              std::endl
	          <<                                                       std::endl
	          << "* Total de hits: "   << cpu.get_cache_hits()   <<    std::endl
	          << "* Total de misses: " << cpu.get_cache_misses() <<    std::endl;
}

void read_and_process_addresses(
	Cpu & cpu,
	Cout_protected & cout, Cerr_protected & cerr,
	char* argv[], unsigned int argc,
	bool debug 
) {
	std::vector<Thread*> threads;

	for(unsigned int i = 2; i < argc ; ++i)   threads.push_back(
		new Read_and_process_addresses(cpu, cout, cerr, argv[i], debug));

	for (Thread* thread : threads)        thread->start();
	for (Thread* thread : threads)        thread->join();
	for (Thread* thread : threads) delete thread;
}

/* Parametros
 * argv[2] = config.cfg 
 * argv[3] = cpu-00.bin, argv[4] = cpu-01.bin ... argv[n] = cpu-n.bin
 */ 

int main(int argc, char* argv[]) {
	Input config;
	Cout_protected cout;
	Cerr_protected cerr;
	Cpu cpu;
	bool debug = false;

	parse_config_cpu(cpu, config, argv[1], debug);
	          
	cout_cpu_specifications(cpu);  

	read_and_process_addresses(cpu, cout, cerr, argv, argc, debug); 

	cout_cache_report(cpu);

    return SUCCESS;
}
