#ifndef MATRIX_REALIZATION_H
#define MATRIX_REALIZATION_H

#include "Matrix.h"

#include <iostream>
#include <cstdlib>
#include <ctime>


#pragma region Constructor/Destructor

// Constructors
template<typename Type>
Matrix<Type>::Matrix()
{
	this->data = nullptr;

	this->element_numb = 0;
	this->n = 0;
	this->m = 0;
}

template<typename Type>
Matrix<Type>::Matrix(size_t n, size_t m)
{
	time_t err_time = time(nullptr);

	if ((n == 0) || (m == 0))
	{
		throw IndexException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Incorrect matrix size");
	}

	this->element_numb = n * m;
	this->n = n;
	this->m = m;

	try
	{
		this->data = std::shared_ptr<Type>(new Type[element_numb]);
	}

	catch (std::bad_alloc)
	{
		throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Allocation error");
	}
}

template<typename Type>
Matrix<Type>::Matrix(const Matrix<Type>& mtrx) : MatrixBase()
{
	time_t err_time = time(nullptr);

	this->n = mtrx.get_n();
	this->m = mtrx.get_m();
	this->element_numb = mtrx.size();

	try
	{
		this->data = std::shared_ptr<Type>(new Type[element_numb]);
	}

	catch (std::bad_alloc)
	{
		throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Allocation error");
	}

	for (size_t i = 0; i < this->n; i++)
	{
		for (size_t j = 0; j < this->m; j++)
		{
			this->data.get()[i * m + j] = mtrx.data.get()[i * m + j];
		}
	}
}

template<typename Type>
Matrix<Type>::Matrix(Matrix<Type>&& mtrx) : MatrixBase()
{
	time_t err_time = time(nullptr);

	this->n = mtrx.get_n();
	this->m = mtrx.get_m();
	this->element_numb = mtrx.size();

	try
	{
		this->data = std::shared_ptr<Type>(new Type[element_numb]);
	}

	catch (std::bad_alloc)
	{
		throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Allocation error");
	}

	for (size_t i = 0; i < this->n; i++)
	{
		for (size_t j = 0; j < this->m; j++)
		{
			this->data.get()[i * m + j] = mtrx.data.get()[i * m + j];
		}
	}
}

template<typename Type>
Matrix<Type>::Matrix(std::initializer_list<std::initializer_list<Type>> list)
{
	time_t err_time = time(nullptr);

	this->n = list.size();
	this->m = list.begin()->size();
	this->element_numb = n * m;

	try
	{
		this->data = std::shared_ptr<Type>(new Type[element_numb]);
	}

	catch (std::bad_alloc)
	{
		throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Allocation error");
	}

	auto iter_i = list.begin();

	for (size_t i = 0; iter_i != list.end(); i++, iter_i++)
	{
		if (this->m != iter_i->size())
		{
			throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Size should be equal");
		}
		else
		{
			auto iter_j = iter_i->begin();

			for (size_t j = 0; iter_j != iter_i->end(); j++, iter_j++)
			{
				this->data.get()[i * this->m + j] = *iter_j;
			}
		}
	}
}

// Destructor
template<typename Type>
Matrix<Type>::~Matrix()
{
	this->data.reset();
	this->n = 0;
	this->m = 0;
}

#pragma endregion


#pragma region Equals

template<typename Type>
Matrix<Type>& Matrix<Type>::operator =(const Matrix<Type>& mtrx)
{
	time_t err_time = time(nullptr);

	size_t n_mtrx = mtrx.get_n();
	size_t m_mtrx = mtrx.get_m();

	this->n = n_mtrx;
	this->m = m_mtrx;
	this->element_numb = mtrx.element_numb;

	try
	{
		this->data = std::shared_ptr<Type>(new Type[element_numb]);
	}

	catch(std::bad_alloc)
	{
		throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Allocation error");
	}

	if ((this->m == m_mtrx) && (this->n == n_mtrx))
	{
		for (size_t i = 0; i < n_mtrx; i++)
		{
			for (size_t j = 0; j < m_mtrx; j++)
			{
				this->data.get()[i * m + j] = mtrx.data.get()[i * m + j];
			}
		}
	}
	else
	{
		throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Size should be equal");
	}

	return *this;
}

template<typename Type>
Matrix<Type>& Matrix<Type>::operator =(Matrix<Type>&& mtrx)
{
	time_t err_time = time(nullptr);

	size_t n_mtrx = mtrx.get_n();
	size_t m_mtrx = mtrx.get_m();

	this->n = n_mtrx;
	this->m = m_mtrx;
	this->element_numb = mtrx.element_numb;

	try
	{
		this->data = std::shared_ptr<Type>(new Type[element_numb]);
	}

	catch (std::bad_alloc)
	{
		throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Allocation error");
	}

	if ((this->m == m_mtrx) && (this->n == n_mtrx))
	{
		for (size_t i = 0; i < n_mtrx; i++)
		{
			for (size_t j = 0; j < m_mtrx; j++)
			{
				this->data.get()[i * m + j] = mtrx.data.get()[i * m + j];
			}
		}
	}
	else
	{
		throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Size should be equal");
	}

	return *this;
}

template<typename Type>
Matrix<Type>& Matrix<Type>::operator =(std::initializer_list<std::initializer_list<Type>> list)
{
	time_t err_time = time(nullptr);

	this->n = list.size();
	this->m = list.begin()->size();
	this->element_numb = n * m;

	try
	{
		this->data = std::shared_ptr<Type>(new Type[element_numb]);
	}

	catch (std::bad_alloc)
	{
		throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Allocation error");
	}

	auto iter_i = list.begin();

	for (size_t i = 0; iter_i != list.end(); i++, iter_i++)
	{
		if (this->m != iter_i->size())
		{
			throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Size should be equal");
		}
		else
		{
			auto iter_j = iter_i->begin();

			for (size_t j = 0; iter_j != iter_i->end(); j++, iter_j++)
			{
				this->data.get()[i * this->m + j] = *iter_j;
			}
		}
	}

	return *this;
}

#pragma endregion


#pragma region Addition

// Private methods
template<typename Type>
void Matrix<Type>::addition(const Matrix<Type>& mtrx) const
{
	for (size_t i = 0; i < this->get_n(); i++)
	{
		for (size_t j = 0; j < this->get_m(); j++)
		{
			this->data.get()[i * this->get_m() + j] += mtrx[i][j];
		}
	}
}

template<typename Type>
void Matrix<Type>::addition(const Type& value) const
{
	for (size_t i = 0; i < this->get_n(); i++)
	{
		for (size_t j = 0; j < this->get_m(); j++)
		{
			this->data.get()[i * this->get_m() + j] += value;
		}
	}
}


// Public methods
template<typename Type>
Matrix<Type> Matrix<Type>::operator +(const Matrix<Type>& mtrx1) const
{
	time_t err_time = time(nullptr);

	if (this->is_empty() || mtrx1.is_empty())
	{
		throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "One of the matrices is empty.");
	}

	if ((mtrx1.get_n() != this->n) && (mtrx1.get_m() != this->m))
	{
		throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Size should be equal");
	}
	else
	{
		Matrix<Type> result(*this);
		result.addition(mtrx1);
		return result;
	}
}

template<typename Type>
Matrix<Type> Matrix<Type>::operator +(const Type& value) const
{
	time_t err_time = time(nullptr);

	if (this->is_empty())
	{
		throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "One of the matrices is empty.");
	}
	else
	{
		Matrix<Type> result(*this);
		result.addition(value);
		return result;
	}
}

template<typename Type>
Matrix<Type>& Matrix<Type>::operator +=(const Matrix<Type>& mtrx)
{
	time_t err_time = time(nullptr);

	if ((this->m == mtrx.get_m()) && (this->n == mtrx.get_n()))
	{
		this->addition(mtrx);
	}
	else
	{
		throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Size should be equal");
	}

	return *this;
}

template<typename Type>
void Matrix<Type>::add(const Matrix<Type>& mtrx) const
{
	time_t err_time = time(nullptr);

	if (this->is_empty() || mtrx.is_empty())
	{
		throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "One of the matrices is empty.");
	}

	if ((this->get_n() != mtrx.get_n()) || (this->get_m() != mtrx.get_m()))
	{
		throw IsNotEqualException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Matrices is not equal.");
	}

	this->addition(mtrx);
}

template<typename Type>
void Matrix<Type>::add(const Type& value) const
{
	time_t err_time = time(nullptr);

	if (this->is_empty())
	{
		throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "One of the matrices is empty.");
	}

	this->addition(value);
}

#pragma endregion


#pragma region Substraction

// Private methods
template<typename Type>
void Matrix<Type>::subtraction(const Matrix<Type>& mtrx) const
{
	for (size_t i = 0; i < this->get_n(); i++)
	{
		for (size_t j = 0; j < this->get_m(); j++)
		{
			this->data.get()[i * this->get_m() + j] -= mtrx[i][j];
		}
	}
}

template<typename Type>
void Matrix<Type>::subtraction(const Type& value) const
{
	for (size_t i = 0; i < this->get_n(); i++)
	{
		for (size_t j = 0; j < this->get_m(); j++)
		{
			this->data.get()[i * this->get_m() + j] -= value;
		}
	}
}


// Public methods
template<typename Type>
Matrix<Type> Matrix<Type>::operator -(const Matrix<Type>& mtrx1) const
{
	time_t err_time = time(nullptr);

	if (this->is_empty() || mtrx1.is_empty())
	{
		throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "One of the matrices is empty.");
	}

	if ((mtrx1.get_n() != this->n) && (mtrx1.get_m() != this->m))
	{
		throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Size should be equal");
	}
	else
	{
		Matrix<Type> result(*this);
		result.subtraction(mtrx1);
		return result;
	}
}

template<typename Type>
Matrix<Type> Matrix<Type>::operator -(const Type& value) const
{
	time_t err_time = time(nullptr);

	if (this->is_empty())
	{
		throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "One of the matrices is empty.");
	}
	else
	{
		Matrix<Type> result(*this);
		result.subtraction(value);
		return result;
	}
}

template<typename Type>
Matrix<Type>& Matrix<Type>::operator -=(const Matrix<Type>& mtrx)
{
	time_t err_time = time(nullptr);

	size_t n_mtrx = mtrx.get_n();
	size_t m_mtrx = mtrx.get_m();

	if ((this->m == m_mtrx) && (this->n == n_mtrx))
	{
		this->subtraction(mtrx);
	}
	else
	{
		throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Size should be equal");
	}

	return *this;
}

template<typename Type>
void Matrix<Type>::sub(const Matrix<Type>& mtrx) const
{
	time_t err_time = time(nullptr);

	if (this->is_empty() || mtrx.is_empty())
	{
		throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "One of the matrices is empty.");
	}

	if ((this->get_n() != mtrx.get_n()) || (this->get_m() != mtrx.get_m()))
	{
		throw IsNotEqualException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Matrices is not equal.");
	}

	this->subtraction(mtrx);
}

template<typename Type>
void Matrix<Type>::sub(const Type& value) const
{
	time_t err_time = time(nullptr);

	if (this->is_empty())
	{
		throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "One of the matrices is empty.");
	}
	else
	{
		this->subtraction(value);
	}
}

#pragma endregion


#pragma region Multiplication

// Private method
template<typename Type>
void Matrix<Type>::multiplicate(const Type& value) const
{
	size_t n = this->n;
	size_t m = this->m;

	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			this->data.get()[i * m + j] *= value;
		}
	}
}


// Public methods
template<typename Type>
Matrix<Type> Matrix<Type>::operator *(const Matrix<Type>& mtrx1) const
{
	time_t err_time = time(nullptr);

	if (this->n != mtrx1.get_m())
	{
		throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Size should be equal");
	}
	else
	{
		size_t n = this->n;
		size_t m = mtrx1.get_m();
		size_t l = this->n;

		Matrix<Type> result = Matrix<Type>(n, m);

		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j < m; j++)
			{
				double temp = 0;
				for (size_t k = 0; k < l; k++)
				{
					temp += mtrx1.data.get()[i * m + j] * this->data.get()[k * m + j];
				}
				result.data.get()[i * m + j] = temp;
			}
		}

		return result;
	}
}

template<typename Type>
Matrix<Type> Matrix<Type>::operator *(const Type& value) const
{
	time_t err_time = time(nullptr);

	if (this->is_empty())
	{
		throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "One of the matrices is empty.");
	}
	else
	{
		Matrix<Type> result(*this);
		result.multiplicate(value);
		return result;
	}
}

template<typename Type>
Matrix<Type>& Matrix<Type>::operator *=(const Matrix<Type>& mtrx)
{
	time_t err_time = time(nullptr);

	if (this->n != mtrx.get_m())
	{
		throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Size should be equal");
	}
	else
	{
		size_t n = this->n;
		size_t m = mtrx.get_m();
		size_t l = this->n;

		Matrix<Type> result = Matrix<Type>(n, m);

		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j < m; j++)
			{
				double element = 0;

				for (size_t k = 0; k < l; k++)
				{
					element += mtrx.data.get()[i * m + k] * this->data.get()[k * m + j];
				}
				result.data.get()[i * m + j] = element;
			}
		}

		return result;
	}
}

template<typename Type>
void Matrix<Type>::mult(const Type& value) const
{
	time_t err_time = time(nullptr);

	if (this->is_empty())
	{
		throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "One of the matrices is empty.");
	}
	else
	{
		this->multiplicate(value);
	}
}

#pragma endregion


#pragma region Division

// Private method
template<typename Type>
void Matrix<Type>::division(const Type& value) const
{
	size_t n = this->n;
	size_t m = this->m;

	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			this->data.get()[i * m + j] /= value;
		}
	}
}


// Public methods
template<typename Type>
Matrix<Type> Matrix<Type>::operator /(const Type& value) const
{
	time_t err_time = time(nullptr);

	if (this->is_empty())
	{
		throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "One of the matrices is empty.");
	}
	else
	{
		Matrix<Type> result(*this);
		result.division(value);
		return result;
	}
}

template<typename Type>
void Matrix<Type>::divide(const Type& value) const
{
	time_t err_time = time(nullptr);

	if (this->is_empty())
	{
		throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "One of the matrices is empty.");
	}
	else
	{
		this->division(value);
	}
}

#pragma endregion


#pragma region Round brackets
template<typename Type>
Type& Matrix<Type>::operator ()(size_t i, size_t j)
{
	time_t err_time = time(nullptr);

	if ((this->n <= i) || (this->m <= j))
	{
		throw IndexException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Index out of range");
	}

	return this->data.get()[i * this->m + j];
}

template<typename Type>
const Type& Matrix<Type>::operator ()(size_t i, size_t j) const
{
	time_t err_time = time(nullptr);

	if ((this->n <= i) || (this->m <= j))
	{
		throw IndexException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Index out of range");
	}

	return this->data.get()[i * this->m + j];
}

#pragma endregion


// Output matrix <<
template<typename _Type>
std::ostream& operator <<(std::ostream& ostream, const Matrix<_Type>& mtrx)
{
	for (size_t i = 0; i < mtrx.get_n(); i++)
	{
		for (size_t j = 0; j < mtrx.get_m(); j++)
		{
			ostream << mtrx.data.get()[i * mtrx.get_m() + j] << "\t";
		}
		ostream << std::endl;
	}

	ostream << std::endl;
	return ostream;
}

#pragma endregion


#pragma region Iterators

template<typename Type>
Iterator<Type> Matrix<Type>::begin()
{
	Iterator<Type> iter(*this, 0);
	return iter;
}

template<typename Type>
Iterator<Type> Matrix<Type>::end()
{
	Iterator<Type> iter(*this, this->n * this->m);
	return iter;
}

template<typename Type>
IteratorConst<Type> Matrix<Type>::begin() const
{
	IteratorConst<Type> iter(*this->data, 0);
	return iter;
}

template<typename Type>
IteratorConst<Type> Matrix<Type>::end() const
{
	IteratorConst<Type> iter(*this->data, this->n * this->m);
	return iter;
}

#pragma endregion


#pragma region Other methods

template<typename Type>
size_t Matrix<Type>::get_n() const
{
	return this->n;
}

template<typename Type>
size_t Matrix<Type>::get_m() const
{
	return this->m;
}

template<typename Type>
const Type& Matrix<Type>::get_value(size_t i, size_t j) const
{
	time_t err_time = time(nullptr);

	if ((i >= this->n) || (j >= this->m))
	{
		throw IndexException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Index out of range");
	}
	else
	{
		if (this->data)
		{
			return data.get()[i * this->m + j];
		}
		else
		{
			throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Allocation error");
		}
	}
}

template<typename Type>
void Matrix<Type>::set_value(size_t i, size_t j, const Type& value)
{
	time_t err_time = time(nullptr);

	if ((i >= this->n) || (j >= this->m))
	{
		throw IndexException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Index out of range");
	}
	else
	{
		if (this->data)
		{
			this->data.get()[i * this->m + j] = value;
		}
		else
		{
			throw IsEmptyException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Allocation error");
		}
	}
}

template<typename Type>
void Matrix<Type>::fill_zero()
{
	for (size_t i = 0; i < this->n; i++)
	{
		for (size_t j = 0; j < this->m; j++)
		{
			this->data.get()[i * this->m + j] = 0;
		}
	}
}

template<typename Type>
void Matrix<Type>::identity_matrix()
{
	for (size_t i = 0; i < this->n; i++)
	{
		for (size_t j = 0; j < this->m; j++)
		{
			if (i != j)
			{
				this->data.get()[i * this->m + j] = 0;
			}
			else
			{
				this->data.get()[i * this->m + j] = 1;
			}
		}
	}
}

#pragma endregion


#endif // !MATRIX_REALIZATION_H