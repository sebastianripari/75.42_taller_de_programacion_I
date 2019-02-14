#include <string>
#include <vector>
#include "cache_direct.h"
#include "lock.h"

#define ERROR -1
#define HIT 1
#define MISS 2

Cache_direct::Cache_direct(
	const unsigned int size,
	const unsigned int line_size
) {
	// Para inicializar los elementos del vector use el numero 0,
	// se podria aver usado otro.
	std::vector<int> v(size/line_size, 0);
	std::vector<bool> b(size/line_size, false);
	this->blocks = std::move(v);
	this->blocks_valid = std::move(b);
	this->size = size;
	this->line_size = line_size;
	this->n_blocks = size/line_size;
	this->hits = 0;
	this->misses = 0;
} 

int Cache_direct::access(const std::string &address) {
	int address_int = std::stoll(address, nullptr, 16);

	if(!this->is_valid(address_int)) return ERROR;	

	int tag = this->get_tag(address_int);

    unsigned int index = tag % n_blocks;

    Lock l(this->m);
    
    if ((this->blocks[index] == tag) && (this->blocks_valid[index] == true)) {
    	++this->hits;
		return HIT;
    } else {
    	++this->misses;
    	this->blocks[index] = tag;
    	this->blocks_valid[index] = true;
		return MISS;
    }
}

unsigned int Cache_direct::get_misses() const {
	return this->misses;
}

unsigned int Cache_direct::get_hits() const {
	return this->hits;
}

Cache_direct::~Cache_direct() {}
