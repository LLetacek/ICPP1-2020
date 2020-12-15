#pragma once
#ifndef _MATRIX_H
#define _MATRIX_H

template<typename T>
class Matrix {
 public:
	 Matrix(unsigned int row, unsigned int column);
	 Matrix(const Matrix<T>& matrix);
	 ~Matrix();
	 void Setter(unsigned int row, unsigned int column, T element);
	 void Setter(T* elements);
	 T& Getter(unsigned int row, unsigned int column);
	 const T& Getter(unsigned int row, unsigned int column) const;
	 Matrix Transposition() const;
	 Matrix Multiply(const Matrix& matrix) const;
	 Matrix Multiply(T scalar) const;
	 Matrix Sum(const Matrix& matrix) const;
	 Matrix Sum(T scalar) const;
	 bool IsMatch(const Matrix& matrix) const;
	 void Print() const;

	 template<typename R>
	 Matrix<R> Cast() const;

 private:
	 void deleteMatrix();
	 T& getElement(unsigned int row, unsigned int column);

	 unsigned int m_row;
	 unsigned int m_col;
	 T** m_elements;
};


template<typename T>
Matrix<T>::Matrix(unsigned int row, unsigned int column) : m_row(row),
														   m_col(column) 
{
	m_elements = new T * [m_row];
	for (unsigned int x = 0; x < m_row; ++x) {
		m_elements[x] = new T[m_col]();
	}
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& matrix) {
	deleteMatrix();
	m_row = matrix.m_row;
	m_col = matrix.m_col;
	m_elements = new T*[m_row];

	for (unsigned int x = 0; x < m_row; ++x) {
		m_elements[x] = new T[m_col]();
		for (unsigned int y = 0; y < m_col; ++y) {
			m_elements[x][y] = matrix.m_elements[x][y];
		}
	}
}

template<typename T>
Matrix<T>::~Matrix() {
	deleteMatrix();
}

template<typename T>
void Matrix<T>::deleteMatrix() {
	if (m_elements == nullptr)
		return;

	for (unsigned int x = 0; x < m_row; ++x) {
		delete[] m_elements[x];
	}
	delete[] m_elements;
}

template<typename T>
void Matrix<T>::Setter(unsigned int row, unsigned int column, T element) {
	getElement(row, column) = element;
}

template<typename T>
void Matrix<T>::Setter(T* elements) {
	for (unsigned int x = 0; x < m_row; ++x) {
		for (unsigned int y = 0; y < m_col; ++y) {
			m_elements[x][y] = elements[x*(m_col) + y];
		}
	}
}

template<typename T>
T& Matrix<T>::Getter(unsigned int row, unsigned int column) {
	return getElement(row, column);
}

template<typename T>
const T& Matrix<T>::Getter(unsigned int row, unsigned int column) const {
	return getElement(row, column);
}

template<typename T>
T& Matrix<T>::getElement(unsigned int row, unsigned int column) {
	if (m_row <= row || m_col <= column)
		throw std::invalid_argument("sahate mimo pole");
	return m_elements[row][column];
}

template<typename T>
template<typename R>
Matrix<R> Matrix<T>::Cast() const {
	Matrix<R> newMatrix{ m_row, m_col };
	for (unsigned int x = 0; x < m_row; ++x) {
		for (unsigned int y = 0; y < m_col; ++y) {
			newMatrix.Getter(x, y) = static_cast<R>(m_elements[x][y]);
		}
	}
	return newMatrix;
}

template<typename T>
Matrix<T> Matrix<T>::Transposition() const {
	Matrix<T> newMatrix{ m_row, m_col };
	for (unsigned int x = 0; x < m_row; ++x) {
		for (unsigned int y = 0; y < m_col; ++y) {
			newMatrix.Getter(x, y) = m_elements[y][x];
		}
	}
	return newMatrix;
}

template<typename T>
Matrix<T> Matrix<T>::Multiply(const Matrix& matrix) const {
	if (m_col != matrix.m_row)
		throw std::invalid_argument("matice nemohou byt vynasobeny");

	Matrix<T> newMatrix{ m_row, matrix.m_col };
	for (unsigned int z = 0; z < matrix.m_col; ++z) {
		for (unsigned int x = 0; x < m_row; ++x) {
			for (unsigned int y = 0; y < m_col; ++y) {
				newMatrix.m_elements[x][z] += m_elements[x][y] * matrix.m_elements[y][z];
			}
		}
	}
	return newMatrix;
}

template<typename T>
Matrix<T> Matrix<T>::Multiply(T scalar) const {
	Matrix<T> newMatrix{ m_row, m_col };
	for (unsigned int x = 0; x < m_row; ++x) {
		for (unsigned int y = 0; y < m_col; ++y) {
			newMatrix.m_elements[x][y] = m_elements[x][y] * scalar;
		}
	}
	return newMatrix;
}

template<typename T>
Matrix<T> Matrix<T>::Sum(const Matrix& matrix) const {
	if(m_row != matrix.m_row || m_col != matrix.m_col)
		throw std::invalid_argument("matice nemohou byt secteny");

	Matrix<T> newMatrix{ m_row, m_col };
	for (unsigned int x = 0; x < m_row; ++x) {
		for (unsigned int y = 0; y < m_col; ++y) {
			newMatrix.m_elements[x][y] = m_elements[x][y] + matrix.m_elements[x][y];
		}
	}
	return newMatrix;
}

template<typename T>
Matrix<T> Matrix<T>::Sum(T scalar) const {
	Matrix<T> newMatrix{ m_row, m_col };
	for (unsigned int x = 0; x < m_row; ++x) {
		for (unsigned int y = 0; y < m_col; ++y) {
			newMatrix.m_elements[x][y] = m_elements[x][y] + scalar;
		}
	}
	return newMatrix;
}

template<typename T>
bool Matrix<T>::IsMatch(const Matrix& matrix) const {
	for (unsigned int x = 0; x < m_row; ++x) {
		for (unsigned int y = 0; y < m_col; ++y) {
			if (matrix.m_elements[x][y] != m_elements[x][y])
				return false;
		}
	}
	return true;
}

template<typename T>
void Matrix<T>::Print() const {
	for (unsigned int x = 0; x < m_row; ++x) {
		for (unsigned int y = 0; y < m_col; ++y) {
			std::cout << m_elements[x][y] << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl;
}

#endif // !_MATRIX_H
