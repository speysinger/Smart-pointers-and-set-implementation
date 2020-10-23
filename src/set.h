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
private:
	RedBlackTree *tree = new RedBlackTree();
};

template<class T>
inline bool set<T>::empty()
{
	return size() == 0 ? true : false;
}

template<class T>
inline int set<T>::size()
{
	return tree->size();
}

template<class T>
inline int set<T>::max_size()
{
	return std::numeric_limits<T>::max();
}

template<class T>
inline void set<T>::clear()
{
	tree->clear();
}

template<class T>
inline void set<T>::insert(T * value)
{
	tree->addNode(value);
}

template<class T>
inline void set<T>::deleteVal(T * value)
{
	tree->deleteNode(value);
}
