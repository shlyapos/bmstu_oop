#ifndef MATRIX_BASE_H
#define MATRIX_BASE_H

#include <iostream>

class MatrixBase
{
public:
	explicit MatrixBase() : element_numb(0) { }
	explicit MatrixBase(size_t n) : element_numb(n) { }
	virtual ~MatrixBase() = default;

	bool is_empty() const { return element_numb == 0; }
	size_t get_rows(void) const { return this->rows; }
	size_t get_columns(void) const { return this->columns; }
	size_t size() const { return element_numb; }

protected:
	size_t rows;
	size_t columns;
	size_t element_numb;
};

#endif // !MATRIX_BASE_H

