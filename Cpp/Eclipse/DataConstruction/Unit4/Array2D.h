//20-09-07 08:13
///模板二维数组类，利用动态内存分配，含有赋值，一元和二元加法，一元和
//二元减法，乘法等基本运算。基本用法是Array2D[i][j]。
#include "Array1D.h"

template<class T>
class Array2D {
public:
	Array2D(int r = 0, int c = 0);
	Array2D(const Array2D<T>& m);
	~Array2D() {
		delete[] row;
	}
	int Rows() const {
		return rows;
	}
	int Columns() const {
		return cols;
	}
	Array1D<T>& operator[](int i) const;
	Array2D<T>& operator=(const Array2D<T>& m);
	Array2D<T> operator+() const;
	Array2D<T> operator+(const Array2D<T>& m) const;
	Array2D<T> operator-() const;
	Array2D<T> operator-(const Array2D<T>& m) const;
	Array2D<T> operator*(const Array2D<T>& m) const;
	Array2D<T>& operator+=(const T& x);
private:
	int rows, cols;
	Array1D<T>* row;
};

template<class T>
Array2D<T>::Array2D(int r, int c) {
	if (r < 0 || c < 0)
		return;
	if (!(r && c) && (r || c))
		return;
	rows = r;
	cols = c;
	row = new Array1D<T> [r];
	for (int i = 0; i < r; i++)
		row[i].Resize(c);
}

template<class T>
Array2D<T>::Array2D(const Array2D<T>& m) {
	rows = m.rows;
	cols = m.cols;
	row = new Array1D<T> [rows];
	for (int i = 0; i < rows; i++)
		row[i] = m.row[i];
}

template<class T>
Array1D<T>& Array2D<T>::operator[](int i) const {
	return row[i];
}

template<class T>
Array2D<T>& Array2D<T>::operator=(const Array2D<T>& m) {
	rows = m.rows;
	cols = m.cols;
	row = new Array1D<T> [rows];
	for (int i = 0; i < rows; i++)
		row[i] = m.row[i];
	return *this;
}

template<class T>
Array2D<T> Array2D<T>::operator-(const Array2D<T>& m) const {
	Array2D<T> w(rows, cols);
	for (int i = 0; i < rows; i++)
		w.row[i] = row[i] - m.row[i];
	return w;
}

template<class T>
Array2D<T> Array2D<T>::operator-() const {
	Array2D<T> w(rows, cols);
	for (int i = 0; i < rows; i++)
		w.row[i] = -row[i];
	return w;
}

template<class T>
Array2D<T> Array2D<T>::operator+(const Array2D<T>& m) const {
	Array2D<T> w(rows, cols);
	for (int i = 0; i < rows; i++)
		w.row[i] = row[i] + m.row[i];
	return w;
}

template<class T>
Array2D<T> Array2D<T>::operator+() const {
	Array2D<T> w(rows, cols);
	for (int i = 0; i < rows; i++)
		w.row[i] = row[i];
	return w;
}

template<class T>
Array2D<T>& Array2D<T>::operator+=(const T& x) {
	for (int i = 0; i < rows; i++)
		row[i] += x;
	return *this;
}

template<class T>
Array2D<T> Array2D<T>::operator*(const Array2D<T>& m) const {
	Array2D<T> w(rows, cols);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < m.rows; j++) {
			T sum = (*this)[i][0] * m[0][j];
			for (int k = 0; k < cols; k++)
				sum += (*this)[i][k] * m[k][j];
			w[i][j] = sum;
		}
	return w;
}

