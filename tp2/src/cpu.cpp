#include <string>
#include "cpu.h"
#include "cache.h"
#include "cache_fa_fifo.h"
#include "cache_fa_lru.h"
#include "cache_direct.h"

Cpu::Cpu() {
	this->cache = nullptr;
}

void Cpu::set_vendor_id(const std::string vendor_id) {
	this->vendor_id = vendor_id;
}

const std::string & Cpu::get_vendor_id() const {
	return this->vendor_id;
}

void Cpu::set_model_name(const std::string model_name) {
	this->model_name = model_name;
}

const std::string & Cpu::get_model_name() const {
	return this->model_name;
}

void Cpu::set_frequency(const std::string frequency) {
	this->frequency = frequency;
}

const std::string & Cpu::get_frequency() const {
	return this->frequency;
}

void Cpu::set_cache_specifications(
	const std::string type,
    const unsigned int size,
    const unsigned int line_size
) {
	if (type == "associative-fifo")
		this->cache = new Cache_fa_fifo(size, line_size);

	else if (type == "associative-lru")
		this->cache = new Cache_fa_lru(size, line_size);

	else if (type == "direct")	
		this->cache = new Cache_direct(size, line_size);
}

int Cpu::access(const std::string & address) {
	return this->cache->access(address);
}

unsigned int Cpu::get_cache_hits() const {
	return this->cache->get_hits();
}

unsigned int Cpu::get_cache_misses() const {
	return this->cache->get_misses();
}

Cpu::~Cpu() {
	delete this->cache;
}
