#pragma once
#include "red-black_tree.h"

template <class T>
class set {
public:
	set();
	set(set &copySet);
	set(set &&copySet);

	//capacity
	bool empty();
	int size();
	int max_size();

	//modifiers
	void clear();

	void insert(T &value);
	void erase(T *value);
	T* find(T &value);

private:
	RedBlackTree<T> *tree;
};

template<class T>
inline set<T>::set()
{
	tree = new RedBlackTree<T>();
}

template<class T>
inline set<T>::set(set &copySet)
{
	this->tree = copySet.tree;
}

template<class T>
inline set<T>::set(set && copySet)
{
	this->tree = copySet.tree;
	copySet.tree = nullptr;
}

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
inline void set<T>::insert(T &value)
{
	tree->addNode(value);
}

template<class T>
inline T * set<T>::find(T &value)
{
	return tree->find(value);
}

template<class T>
inline void set<T>::erase(T * value)
{
	tree->deleteNode(value);
}
