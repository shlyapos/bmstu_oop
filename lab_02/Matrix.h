#ifndef MATRIX_H
#define MATRIX_H

#include "MatrixBase.h"
#include "MatrixBaseException.h"

#include "Iterator.h"
#include "IteratorConst.h"

#include <iostream>
#include <stdio.h>
#include <typeinfo>
#include <time.h>

template<typename Type>
class Matrix : public MatrixBase
{
	friend Iterator<Type>;
	friend IteratorConst<Type>;
public:
	// Constructors
	Matrix();
	Matrix(size_t n, size_t m);
	explicit Matrix(const Matrix<Type>& mtrx);
	Matrix(Matrix<Type>&& mtrx);
	Matrix(std::initializer_list<std::initializer_list<Type>> list);
	
	// Destructor
	~Matrix(); 

	// Operators equal
	Matrix<Type>& operator =(const Matrix<Type>& mtr);
	Matrix<Type>& operator =(Matrix<Type>&& mtr);
	Matrix<Type>& operator =(std::initializer_list<std::initializer_list<Type>> list);

	// Addition
	Matrix<Type> operator +(const Matrix<Type>& mtrx1) const;
	Matrix<Type> operator +(const Type& value) const;
	Matrix<Type>& operator +=(const Matrix<Type>& mtrx);
	void add(const Matrix<Type>& mtrx) const;
	void add(const Type& value) const;

	// Substraction
	Matrix<Type> operator -(const Matrix<Type>& mtrx1) const;
	Matrix<Type> operator -(const Type& value) const;
	Matrix<Type>& operator -=(const Matrix<Type>& mtrx);
	void sub(const Matrix<Type>& mtrx) const;
	void sub(const Type& value) const;

	// Multiplication
	Matrix<Type> operator *(const Matrix<Type>& mtrx1) const;
	Matrix<Type> operator *(const Type& value) const;
	Matrix<Type>& operator *=(const Matrix<Type>& mtrx);
	void mult(const Type& value) const;

	// Division
	Matrix<Type> operator /(const Type& value) const;
	void divide(const Type& value) const;

	Type& operator ()(size_t i, size_t j);
	const Type& operator ()(size_t i, size_t j) const;

	template<typename _Type>
	friend std::ostream& operator <<(std::ostream& os, const Matrix<_Type>& mtrx);
	
	// Iterators
	Iterator<Type> begin();
	Iterator<Type> end();

	IteratorConst<Type> begin() const;
	IteratorConst<Type> end() const;

	// Other methods
	size_t get_n() const;
	size_t get_m() const;

	const Type& get_value(size_t i, size_t j) const;
	void set_value(size_t i, size_t j, const Type& value);

	void fill_zero();
	void identity_matrix();

	class MatrixRow
	{
		friend Matrix;
	public:
		const Type& operator [](size_t column) const
		{
			time_t err_time = time(nullptr);

			if (column >= this->parent.get_m())
			{
				throw IndexException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Index out of range");
			}

			return parent.data.get()[number * parent.get_m() + column];
		}

		Type& operator [](size_t column)
		{
			time_t err_time = time(nullptr);

			if (column >= this->parent.get_m())
			{
				throw IndexException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Index out of range");
			}

			return parent.data.get()[number * parent.get_m() + column];
		}

	private:
		MatrixRow(const Matrix<Type>& parent, size_t row) : parent(parent), number(row) {  }
		const Matrix& parent;
		size_t number;
	};

	const MatrixRow operator [](size_t row) const
	{
		time_t err_time = time(nullptr);

		if (row >= this->get_n())
		{
			throw IndexException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Index out of range");
		}

		return MatrixRow(*this, row);
	}

	MatrixRow operator [](size_t row)
	{
		time_t err_time = time(nullptr);

		if (row >= this->get_n())
		{
			throw IndexException(__FILE__, typeid(*this).name(), __LINE__ - 4, err_time, "Index out of range");
		}

		return MatrixRow(*this, row);
	}
 
private:
	size_t n;
	size_t m;
	std::shared_ptr<Type> data;

	void addition(const Matrix<Type>& mtrx) const;
	void addition(const Type& value) const;

	void subtraction(const Matrix<Type>& mtrx) const;
	void subtraction(const Type& value) const;

	void multiplicate(const Type& value) const;
	void division(const Type& value) const; 
};

#endif // !MATRIX_H

