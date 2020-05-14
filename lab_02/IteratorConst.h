#ifndef ITERATOR_CONST_H
#define ITERATOR_CONST_H

#include <memory>
#include <string>

#include "MatrixBaseException.h"

template<typename Type>
class Matrix;

template<typename Type>
class IteratorConst : public std::iterator<std::input_iterator_tag, Type>
{
public:
	IteratorConst(const Matrix<Type>& mtrx, const size_t index = 0)
		: _data(mtrx.data), _index(index), _rows(mtrx.get_n()), _cols(mtrx.get_m()) {  }

	IteratorConst(const IteratorConst& iter) = default;

	bool operator !=(IteratorConst const& other) const { return _index != other._index; }
	bool operator ==(IteratorConst const& other) const { return _index == other._index; }

	// Addition
	IteratorConst<Type>& operator ++() const
	{
		if (_index < _cols * _rows)
		{
			++_index;
		}

		return *this;
	}
	IteratorConst<Type>& operator ++(int) const
	{
		IteratorConst<Type> iter(*this);
		++(*this);
		return iter;
	}
	IteratorConst<Type> operator +(const int value) const
	{
		IteratorConst<Type> iter(*this);

		if (value < 0 && iter._index < static_cast<size_t>(-value))
		{
			iter._index = 0;
		}
		else
		{
			iter._index += value;
		}

		if (iter._index > _rows * _cols)
		{
			iter._index = _rows * _cols;
		}

		return iter;
	}
	IteratorConst<Type>& operator +=(const size_t value) const
	{
		_index += value;
		return *this;
	}

	// Substraction
	IteratorConst<Type>& operator --() const
	{
		if (_index < _cols * _rows)
		{
			--_index;
		}

		return *this;
	}
	IteratorConst<Type>& operator --(int) const
	{
		IteratorConst<Type> iter(*this);
		--(*this);
		return iter;
	}
	IteratorConst<Type>& operator -=(const size_t value) const
	{
		_index -= value;
		return *this;
	}
	IteratorConst<Type> operator -(const int value) const
	{
		return operator +(-value);
	}

	// Pointers
	const Type& operator *() const
	{
		check_valid(__LINE__);
		check_index(__LINE__);

		std::shared_ptr<Type> ptr_cpy = _data.lock();
		return *(ptr_cpy.get() + _index);
	}
	Type& operator ->() const
	{
		check_valid(__LINE__);
		check_index(__LINE__);

		std::shared_ptr<Type> ptr_cpy = _data.lock();
		return ptr_cpy.get() + _index;
	}

	// Other methods
	operator bool() const { return _data.expired(); }
	bool is_end() const { return _index == _rows * _cols; }
	bool is_valid() const { return !_data.expired(); }
	IteratorConst<Type>& next() const { return operator ++(); }

private:
	std::weak_ptr<Type> _data = nullptr;
	size_t _index = 0;
	size_t _rows = 0;
	size_t _cols = 0;

	void check_valid(size_t line)
	{
		time_t err_time = time(nullptr);

		if (!is_valid())
		{
			throw IsEmptyException(__FILE__, typeid(*this).name(), line - 4, err_time, "Pointer is null");
		}
	}
	void check_index(size_t line)
	{
		time_t err_time = time(nullptr);

		if (_index > _rows * _cols)
		{
			throw IndexException(__FILE__, typeid(*this).name(), line - 4, err_time, "Index error");
		}
	}
};

#endif // !ITERATOR_CONST_H