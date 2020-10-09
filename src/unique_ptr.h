#pragma once
template<class T>
class unique_ptr
{
public:
	unique_ptr();
	unique_ptr(T *t);
	unique_ptr(unique_ptr& ptr) = delete;
	unique_ptr(unique_ptr&& ptr);

	unique_ptr* operator=(unique_ptr&& ptr) {
		if (this != &ptr) {
			delete m_ptr;

			m_ptr = ptr.m_ptr;
			ptr.m_ptr = nullptr;
		}
		return this;
	}	
	unique_ptr* operator=(unique_ptr& ptr) = delete;

	T& operator*();
	T* operator->();

	//Modifiers
	T* release();
	void swap(unique_ptr &ptr);
	void reset(T *newObject);

	~unique_ptr(); 
private:
	T *m_ptr = nullptr;
};

template<class T>
inline unique_ptr<T>::unique_ptr()
{
}

template<class T>
inline unique_ptr<T>::unique_ptr(T * t)
{
	if (m_ptr != t)
		m_ptr = t;
}

template<class T>
inline T&unique_ptr<T>::operator*()
{
	return *m_ptr;
}

template<class T>
inline T* unique_ptr<T>::operator->()
{
	return m_ptr;
}

template<class T>
inline unique_ptr<T>::unique_ptr(unique_ptr&& ptr)
{
	delete m_ptr;
	m_ptr = ptr.m_ptr;
	ptr.m_ptr = nullptr;
}

template<class T>
inline unique_ptr<T>::~unique_ptr()
{
	delete m_ptr;
}

template<class T>
inline T * unique_ptr<T>::release()
{
	T *pointer = m_ptr;
	m_ptr = nullptr;
	return pointer;
}

template<class T>
inline void unique_ptr<T>::swap(unique_ptr &ptr)
{
	T *temp = m_ptr;
	this->m_ptr = ptr.m_ptr;
	ptr.m_ptr = temp;
}

template<class T>
inline void unique_ptr<T>::reset(T * newObject)
{
	T *temp = m_ptr;
	m_ptr = newObject;

	if (temp)
		delete temp;
}