#ifndef MATRIX_HPP
#define MATRIX_HPP

template <size_t rows, size_t cols>
class Matrix {
private:
	double mData[rows][cols];

public:
	const char* ToString() const;

	const Matrix<rows, cols>& operator*(const Matrix<rows, cols>&
		vrcRHS) const {

	}
};

template <size_t entries>
class Vector {
private:
	double mData[entries];

public:
	Vector(double elems[entries]);
};
#endif