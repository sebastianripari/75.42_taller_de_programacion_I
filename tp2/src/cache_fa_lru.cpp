#include <string>
#include "cache_fa_lru.h"
#include "lock.h"

#define ERROR  -1
#define HIT 1
#define MISS 2

Cache_fa_lru::Cache_fa_lru(
	const unsigned int size,
 	const unsigned int line_size
 ) {
	this->size = size;
	this->line_size = line_size;
	this->n_blocks = size/line_size;
	this->hits = 0;
	this->misses = 0;
}
	
int Cache_fa_lru::access(const std::string &address) {
	int address_int = std::stoll(address, nullptr, 16);

	if(!this->is_valid(address_int)) return ERROR;	

	int tag = this->get_tag(address_int);

	Lock l(this->m);

	if (this->blocks.find(tag)) {
		this->blocks.erase(tag);
		this->blocks.push_front(tag);
		++this->hits;
		return HIT;
	} else {
		if(this->blocks.size() == this->n_blocks) this->blocks.pop_back();
		this->blocks.push_front(tag);
		++this->misses;
		return MISS;
	}
}

unsigned int Cache_fa_lru::get_misses() const {
	return this->misses;
}
	
unsigned int Cache_fa_lru::get_hits() const {
	return this->hits;
}

Cache_fa_lru::~Cache_fa_lru() {}
