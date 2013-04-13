//20-09-07 08:05
//模板矩阵类，利用一维动态内存分配，含有赋值，一元和二元加法，一元和
//二元减法，乘法 ，转置等基本运算。基本用法是M(i,j)。
template<class T>
class Matrix {
public:
	Matrix(int r = 0, int c = 0);
	Matrix(const Matrix<T>&);
	~Matrix() {
		delete[] element;
	}
	int Rows() const {
		return rows;
	}
	int Columns() const {
		return cols;
	}
	T& operator()(int i, int j) const;
	Matrix<T>& operator=(const Matrix<T>&);
	Matrix<T> operator+() const;
	Matrix<T> operator+(const Matrix<T>&) const;
	Matrix<T> operator-() const;
	Matrix<T> operator-(const Matrix<T>&) const;
	Matrix<T> operator*(const Matrix<T>&) const;
	void Transpose(Matrix<T>&) const;
	Matrix<T>& operator+=(const T& x);
private:
	int rows, cols;
	T* element;
};

template<class T>
Matrix<T>::Matrix(int r, int c) {
	rows = r;
	cols = c;
	element = new T[r * c];
}

template<class T>
T& Matrix<T>::operator()(int i, int j) const {
	return element[(i - 1) * cols + j - 1];
}

template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& m) const {
	Matrix<T> w(rows, cols);
	for (int i = 0; i < rows * cols; i++)
		w.element[i] = element[i] - m.element[i];
	return w;
}

template<class T>
Matrix<T> Matrix<T>::operator-() const {
	Matrix<T> w(rows, cols);
	for (int i = 0; i < rows * cols; i++)
		w.element[i] = -element[i];
	return w;
}

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& m) const {
	Matrix<T> w(rows, cols);
	for (int i = 0; i < rows * cols; i++)
		w.element[i] = element[i] + m.element[i];
	return w;
}

template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m) {
	delete[] element;
	rows = m.rows;
	cols = m.cols;
	element = new T[rows * cols];
	for (int i = 0; i < rows * cols; i++)
		element[i] = m.element[i];
	return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator+=(const T& x) {
	for (int i = 0; i < rows * cols; i++)
		element[i] += x;
	return *this;
}

template<class T>
Matrix<T> Matrix<T>::operator+() const {
	Matrix<T> w(rows, cols);
	for (int i = 0; i < rows * cols; i++)
		w.element[i] = element[i];
	return w;
}

template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& m) const {
	Matrix<T> w(rows, m.cols);
	int ct = 0, cm = 0, cw = 0;
	for (int i = 1; i <= rows; i++) {
		for (int j = 1; j <= m.cols; j++) {
			T sum = element[ct] * m.element[cm];
			for (int k = 2; k <= cols; k++) {
				ct++;
				cm += m.cols;
				sum += element[ct] * m.element[cm];
			}
			w.element[cw++] = sum;
			ct -= cols - 1;
			cm = j;
		}
		ct += cols;
		cm = 0;
	}
	return w;
}

template<class T>
void Matrix<T>::Transpose(Matrix<T>& w) const {
	for (int i = 1; i <= cols; i++)
		for (int j = 1; j <= rows; j++)
			w(i, j) = (*this)(j, i);
}

