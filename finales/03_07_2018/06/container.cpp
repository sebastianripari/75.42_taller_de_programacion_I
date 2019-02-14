#include "container.h"

template<class T> void Container<T>::add(T element) {
	this->bag.insert(element);
}

template<class T> void Container<T>::remove(T element) {
	this->bag.erase(element);
}
