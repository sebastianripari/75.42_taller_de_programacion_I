#include <mutex>
#include <deque>
#include <map>
#include <algorithm>

#include "deque.h"
#include "lock.h" 

bool Deque::find(const int i) {
 	if (this->table.find(i) == this->table.end()) 
  		return false;
  	else 
  	 	return true;
}

unsigned int Deque::size() {
	return this->q.size();
}

void Deque::pop_back() {
	this->table.erase(this->q.back());
	this->q.pop_back();
}

void Deque::push_front(const int i) {
	this->table[i] = true;
	this->q.push_front(i);
}

void Deque::erase(const int i) {
	this->table.erase(i);
	this->q.erase(std::find(this->q.begin(), this->q.end(), i));
}

