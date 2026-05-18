#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <stdexcept>

template <typename T>
class Array
{
	private:
		T				*_array;
		unsigned int	_size;

	public:
		Array(void) : _array(NULL), _size(0) {}

		Array(unsigned int n) : _array(new T[n]()), _size(n) {}

		Array(Array const &src) : _array(NULL), _size(0)
		{
			*this = src;
		}

		~Array(void)
		{
			delete[] _array;
		}

		Array &operator=(Array const &rhs)
		{
			if (this != &rhs)
			{
				delete[] _array;
				_size = rhs._size;
				_array = new T[_size]();
				for (unsigned int i = 0; i < _size; i++)
					_array[i] = rhs._array[i];
			}
			return *this;
		}

		T &operator[](unsigned int index)
		{
			if (index >= _size)
				throw std::out_of_range("Array index out of bounds");
			return _array[index];
		}

		T const &operator[](unsigned int index) const
		{
			if (index >= _size)
				throw std::out_of_range("Array index out of bounds");
			return _array[index];
		}

		unsigned int size(void) const
		{
			return _size;
		}
};

#endif
