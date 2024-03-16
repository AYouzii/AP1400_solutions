#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

template<typename T>
class SharedPtr
{
private:
	T* _p;
	unsigned* reference_counting;
public:
	SharedPtr(T* ptr);
	SharedPtr();
	~SharedPtr();
	SharedPtr(const SharedPtr<T>& another_ptr);
	SharedPtr<T>& operator=(const SharedPtr<T>& another_ptr);	
	unsigned use_count() const;
	T* get() const;
	T& operator*() const;
	T* operator->() const;
	void reset();
	void reset(T* new_ptr);
	operator bool() const;
};

template<typename T>
SharedPtr<T> make_shared(T* ptr);

template<typename T>
SharedPtr<T>::SharedPtr(T* ptr)
	: _p(ptr)
{
	if (ptr) {
		reference_counting = new unsigned(1);
	}
	else {
		reference_counting = nullptr;
	}
}

template<typename T>
SharedPtr<T> make_shared(T value)
{
	SharedPtr<T> new_ptr(new T(value));
	return new_ptr;
}

template<typename T>
SharedPtr<T>::SharedPtr()
	: _p(nullptr), reference_counting(nullptr) {}

template<typename T>
SharedPtr<T>::~SharedPtr()
{
	if (_p) {
		// does point to something
		--(*reference_counting);
		if (*reference_counting == 0) {
			delete _p;
			_p = nullptr;
			delete reference_counting;
			reference_counting = nullptr;
		}
		else {
			_p = nullptr;
			reference_counting = nullptr;
		}
	}
}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& another_ptr)
{
	if (another_ptr._p) {
		_p = another_ptr._p;
		reference_counting = another_ptr.reference_counting;
		++(*reference_counting);
	}
	else {
		_p = nullptr;
		reference_counting = new unsigned(0);
	}
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& another_ptr)
{
	if (another_ptr._p == _p) {
		// assignment to itself
		return *this;
	}
	
	if (another_ptr._p) {
		_p = another_ptr._p;
		reference_counting = another_ptr.reference_counting;
		++(*reference_counting);
	}
	else {
		_p = nullptr;
		reference_counting = new unsigned(0);
	}
	return *this;
}

template<typename T>
unsigned SharedPtr<T>::use_count() const
{
	if (_p) {
		return *reference_counting;
	}
	else {
		return 0;
	}
}

template<typename T>
T* SharedPtr<T>::get() const
{
	return _p;
}

template<typename T>
T& SharedPtr<T>::operator*() const
{
	return *_p;
}

template<typename T>
T* SharedPtr<T>::operator->() const
{
	return _p;
}

template<typename T>
void SharedPtr<T>::reset()
{
	if (_p) {
		--(*reference_counting);
		if (*reference_counting == 0) {
			delete _p;
			_p = nullptr;
			delete reference_counting;
			reference_counting = nullptr;
		}
		else {
			_p = nullptr;
			reference_counting = nullptr;
		}
	}	
}

template<typename T>
void SharedPtr<T>::reset(T* new_ptr)
{
	if (_p) {
		--(*reference_counting);
		if (*reference_counting == 0) {
			delete _p;
			_p = new_ptr;
			delete reference_counting;
			reference_counting = new unsigned(1);
		}
		else {
			_p = new_ptr;
			reference_counting = new unsigned(1);
		}
	}
	else {
		_p = new_ptr;
		reference_counting = new unsigned(1);
	}
}

template<typename T>
SharedPtr<T>::operator bool() const
{
	return _p != nullptr;
}

#endif