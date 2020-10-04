#pragma once
template<class T>
class unique_ptr
{
public:
	unique_ptr();
	unique_ptr(T *t);
	unique_ptr(unique_ptr& ptr);
	unique_ptr(unique_ptr&& ptr);

	unique_ptr* operator=(unique_ptr&& ptr) {
		if (this != &ptr) {
			delete object;

			object = ptr.object;
			ptr.object = nullptr;
		}
		return this;
	}

	T& operator*();
	T* operator->();


	~unique_ptr();
private:
	T *object = nullptr;
};

template<class T>
inline unique_ptr<T>::unique_ptr()
{
}

template<class T>
inline unique_ptr<T>::unique_ptr(T * t)
{
	if (object != t)
		object = t;
}

template<class T>
inline T&unique_ptr<T>::operator*()
{
	return *object;
}

template<class T>
inline T* unique_ptr<T>::operator->()
{
	return object;
}


template<class T>
inline unique_ptr<T>::unique_ptr(unique_ptr & ptr)
{
	delete object;
	object = ptr.object;
	ptr.object = nullptr;
}

template<class T>
inline unique_ptr<T>::unique_ptr(unique_ptr&& ptr)
{
	delete object;
	object = ptr.object;
	ptr.object = nullptr;
}

template<class T>
inline unique_ptr<T>::~unique_ptr()
{
	delete object;
}
