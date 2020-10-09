#pragma once
template<class T>
class shared_ptr
{
public:
	shared_ptr();
	shared_ptr(T *t);
	shared_ptr(shared_ptr& ptr);
	shared_ptr(shared_ptr&& ptr);

	shared_ptr* operator=(shared_ptr&& ptr) {
		if (this != &ptr) {
			reset(nullptr);
			m_ptr = ptr.m_ptr;
			counter = counter;

			ptr.m_ptr = nullptr;
			ptr.counter = 0;
		}
		return this;
	}
	shared_ptr* operator=(shared_ptr& ptr) {
		if (this != &ptr) {
			reset(nullptr);
			m_ptr = ptr.m_ptr;
			ptr.counter++;
			counter = ptr.counter;
		}
		return this;
	}

	T& operator*();
	T* operator->();

	//Modifiers
	void swap(shared_ptr &ptr);
	void reset(T *newObject);

	//Observers
	int user_count();
	bool unique();
	operator bool();

	~shared_ptr();
private:
	T *m_ptr = nullptr;
	size_t counter = 0;
};

template<class T>
inline shared_ptr<T>::shared_ptr()
{
}

template<class T>
inline shared_ptr<T>::shared_ptr(T * t)
{
	if (t != nullptr)
	{
		m_ptr = t;
		counter++;
	}
}

template<class T>
inline shared_ptr<T>::shared_ptr(shared_ptr & ptr)
{
	m_ptr = ptr.m_ptr;
	ptr.counter++;
	counter = ptr.counter;
}

template<class T>
inline shared_ptr<T>::shared_ptr(shared_ptr && ptr)
{
	m_ptr = ptr.m_ptr;
	counter = counter;
}

template<class T>
inline T&shared_ptr<T>::operator*()
{
	return *m_ptr;
}

template<class T>
inline T* shared_ptr<T>::operator->()
{
	return m_ptr;
}

template<class T>
inline void shared_ptr<T>::swap(shared_ptr & ptr)
{
	if (this != &ptr) {
		int tempCounter = counter;
		T * tempObject = m_ptr;

		m_ptr = ptr.m_ptr;
		counter = ptr.counter;

		ptr.m_ptr = tempObject;
		ptr.counter = counter;
	}
}

template<class T>
inline void shared_ptr<T>::reset(T * newObject)
{
	if (counter == 1)
		delete m_ptr;
	m_ptr = newObject;
	counter = 1;

}

template<class T>
inline int shared_ptr<T>::user_count()
{
	return counter;
}

template<class T>
inline bool shared_ptr<T>::unique()
{
	if (counter == 1)
		return true;
	return false;
}

template<class T>
inline shared_ptr<T>::operator bool()
{
	if (m_ptr == nullptr)
		return false;
	return true;
}

template<class T>
inline shared_ptr<T>::~shared_ptr()
{
	reset(nullptr);
}
