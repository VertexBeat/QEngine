#pragma once
template<class T>
class TSingleton
{
protected:
	static T * _pSingleton;
public:
	inline TSingleton() {}
	// Gets the Pointer of the new initialized instance, if empty
	inline static T* Get()
	{
		if (!_pSingleton)
			_pSingleton = new T;
		return _pSingleton;
	}

	// Deletes the Pointer to the instance
	static void Del()
	{
		if (_pSingleton)
		{
			delete _pSingleton;
			_pSingleton = nullptr;
		}
	}
};
template <class T>
T* TSingleton<T>::_pSingleton = 0;
