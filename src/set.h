#pragma once
#include "red-black_tree.h"

template <class T>
class set {
public:
	set();

	//capacity
	bool empty();
	int size();
	int max_size();

	//modifiers
	void clear();
	void insert(T *value);
	void deleteVal(T *value); //interim

};