#ifndef UNIQUE_PTR_HPP
#define UNIQUE_PTR_HPP

template<typename T>
class UniquePtr
{
public:
	UniquePtr(T* ptr);
	UniquePtr();
	~UniquePtr();
	UniquePtr(const UniquePtr&) =delete;
	UniquePtr& operator=(const UniquePtr&) =delete;
	T* get() const;
	T& operator*() const;
	T* operator->() const;
	void reset();
	void reset(T* ptr);
	T* release();
	operator bool() const;

private:
	T* _p;
};

template<typename T>
UniquePtr<T> make_unique(T value);

template<typename T>
UniquePtr<T> make_unique(T value)
{
	return UniquePtr<T>(new T(value));
}

template<typename T>
UniquePtr<T>::UniquePtr(T* ptr)
	: _p(std::move(ptr)) {}

template<typename T>
UniquePtr<T>::UniquePtr()
	: _p(nullptr) {}

template<typename T>
UniquePtr<T>::~UniquePtr()
{
	delete _p;
	_p = nullptr;
}

template<typename T>
T* UniquePtr<T>::get() const
{
	return _p;
}

template<typename T>
T& UniquePtr<T>::operator*() const
{
	return *_p;
}

template<typename T>
T* UniquePtr<T>::operator->() const
{
	return _p;
}

template<typename T>
void UniquePtr<T>::reset()
{
	delete _p;
	_p = nullptr;
}

template<typename T>
void UniquePtr<T>::reset(T* ptr)
{
	delete _p;
	_p = std::move(ptr);
}

template<typename T>
T* UniquePtr<T>::release()
{
	T* new_ptr = _p;
	_p = nullptr;
	return new_ptr;
}

template<typename T>
UniquePtr<T>::operator bool() const
{
	return _p != nullptr;
}
#endif // UNIQUE_PTR_HPP