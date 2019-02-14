#ifndef __SET_PROTECTED_H__
#define __SET_PROTECTED_H__

#include <set>
#include <mutex>

class Set_protected {
	std::set<int> q;
	std::mutex m;

public:
	void insert(int i) {
		m.lock();
		this->q.insert(i);
		m.unlock();
	}

	void erase(int i) {
		m.lock();
		this->q.erase(i);
		m.unlock();
	}

	int size() {
		m.lock();
		int size = this->q.size();
		m.unlock();
		return size;
	}
};

#endif
